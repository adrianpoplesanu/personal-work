"""
Training script for tic-tac-toe neural network using self-play
"""
import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
import random
from collections import deque
from game import TicTacToe, Player
from model import TicTacToeNet
import os


class SelfPlayTrainer:
    def __init__(self, model, lr=0.001, batch_size=32, memory_size=10000):
        self.model = model
        self.optimizer = optim.Adam(model.parameters(), lr=lr)
        self.memory = deque(maxlen=memory_size)
        self.batch_size = batch_size
        self.device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
        self.model.to(self.device)
    
    def play_game(self, epsilon=0.1, temperature=1.0):
        """
        Play a self-play game and collect training data
        Returns: list of (state, policy_target, value_target) tuples
        """
        game = TicTacToe()
        game_data = []
        states = []
        
        while not game.game_over:
            state = game.get_state()
            valid_moves = game.get_valid_moves()
            current_player = game.current_player  # Track whose turn it is
            
            if not valid_moves:
                break
            
            # Get model prediction
            value, policy = self.model.predict(state, valid_moves)
            
            # Add exploration noise
            if random.random() < epsilon:
                # Random move
                move = random.choice(valid_moves)
            else:
                # Choose move based on policy with temperature
                if temperature > 0:
                    # Apply temperature to policy
                    logits = np.log(policy + 1e-10) / temperature
                    exp_logits = np.exp(logits - np.max(logits))
                    probs = exp_logits / np.sum(exp_logits)
                    # Only sample from valid moves
                    valid_probs = np.array([probs[m] if m in valid_moves else 0 for m in range(9)])
                    valid_probs = valid_probs / np.sum(valid_probs)
                    move = np.random.choice(9, p=valid_probs)
                else:
                    # Greedy selection
                    valid_policy = {m: policy[m] for m in valid_moves}
                    move = max(valid_policy, key=valid_policy.get)
            
            # Store state, move, and current player
            states.append((state.copy(), move, valid_moves, current_player))
            
            # Make move
            valid, reward = game.make_move(move)
            if not valid:
                break
        
        # Determine final outcome
        if game.winner == Player.X:
            final_value = 1.0
        elif game.winner == Player.O:
            final_value = 0.0
        else:
            final_value = 0.5  # Draw
        
        # Create training data with proper value targets
        # Value from perspective of the player whose turn it was
        for state, move, valid_moves, player in states:
            # Value from perspective of the player whose turn it was
            if player == Player.X:
                # X's perspective: X wins = 1, O wins = 0, draw = 0.5
                value_target = final_value
            else:
                # O's perspective: O wins = 1, X wins = 0, draw = 0.5
                value_target = 1.0 - final_value
            
            # Create policy target (one-hot for the move that was made)
            policy_target = np.zeros(9)
            policy_target[move] = 1.0
            
            game_data.append((state, policy_target, value_target))
        
        return game_data
    
    def train_step(self):
        """Perform one training step on a batch from memory"""
        if len(self.memory) < self.batch_size:
            return None
        
        # Sample batch
        batch = random.sample(self.memory, self.batch_size)
        states = torch.FloatTensor([item[0] for item in batch]).to(self.device)
        policy_targets = torch.FloatTensor([item[1] for item in batch]).to(self.device)
        value_targets = torch.FloatTensor([item[2] for item in batch]).to(self.device)
        
        # Forward pass
        values, policy_logits = self.model(states)
        
        # Compute losses
        # Value loss (MSE)
        value_loss = nn.MSELoss()(values, value_targets)
        
        # Policy loss (cross-entropy)
        policy_loss = nn.CrossEntropyLoss()(policy_logits, policy_targets.argmax(dim=1))
        
        # Total loss
        total_loss = value_loss + policy_loss
        
        # Backward pass
        self.optimizer.zero_grad()
        total_loss.backward()
        self.optimizer.step()
        
        return {
            'total_loss': total_loss.item(),
            'value_loss': value_loss.item(),
            'policy_loss': policy_loss.item()
        }
    
    def train(self, num_games=1000, games_per_batch=10, epsilon=0.3, temperature=1.0):
        """
        Train the model using self-play
        Args:
            num_games: Total number of self-play games
            games_per_batch: Number of games to play before training
            epsilon: Exploration rate
            temperature: Temperature for policy sampling
        """
        print(f"Starting training on {self.device}...")
        print(f"Total games: {num_games}, Games per batch: {games_per_batch}")
        
        for game_num in range(num_games):
            # Play games and collect data
            for _ in range(games_per_batch):
                game_data = self.play_game(epsilon=epsilon, temperature=temperature)
                self.memory.extend(game_data)
            
            # Train on collected data
            loss_info = self.train_step()
            
            # Decay epsilon
            epsilon = max(0.01, epsilon * 0.9995)
            
            # Print progress
            if (game_num + 1) % 10 == 0 or loss_info is None:
                if loss_info:
                    print(f"Game {game_num + 1}/{num_games} - "
                          f"Loss: {loss_info['total_loss']:.4f} "
                          f"(Value: {loss_info['value_loss']:.4f}, "
                          f"Policy: {loss_info['policy_loss']:.4f}) "
                          f"Epsilon: {epsilon:.3f} Memory: {len(self.memory)}")
                else:
                    print(f"Game {game_num + 1}/{num_games} - Collecting data... (Memory: {len(self.memory)})")
        
        print("Training complete!")
    
    def save_model(self, filepath):
        """Save the trained model"""
        torch.save(self.model.state_dict(), filepath)
        print(f"Model saved to {filepath}")
    
    def load_model(self, filepath):
        """Load a trained model"""
        self.model.load_state_dict(torch.load(filepath, map_location=self.device))
        self.model.eval()
        print(f"Model loaded from {filepath}")


def main():
    # Create model
    model = TicTacToeNet(hidden_size=128)
    
    # Create trainer
    trainer = SelfPlayTrainer(model, lr=0.001, batch_size=64, memory_size=20000)
    
    # Train
    trainer.train(num_games=500, games_per_batch=10, epsilon=0.3, temperature=1.0)
    
    # Save model
    os.makedirs('models', exist_ok=True)
    trainer.save_model('models/tic_tac_toe_model.pth')


if __name__ == '__main__':
    main()

