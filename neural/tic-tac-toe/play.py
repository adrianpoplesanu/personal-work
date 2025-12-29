"""
Play against the trained neural network
"""
import torch
import numpy as np
from game import TicTacToe, Player
from model import TicTacToeNet
import os


class GamePlayer:
    def __init__(self, model_path='models/tic_tac_toe_model.pth'):
        self.model = TicTacToeNet(hidden_size=128)
        if os.path.exists(model_path):
            self.model.load_state_dict(torch.load(model_path, map_location='cpu'))
            self.model.eval()
            print(f"Loaded model from {model_path}")
        else:
            print(f"Warning: Model not found at {model_path}. Using untrained model.")
    
    def get_model_move(self, game):
        """Get the best move from the neural network"""
        state = game.get_state()
        valid_moves = game.get_valid_moves()
        
        if not valid_moves:
            return None
        
        value, policy = self.model.predict(state, valid_moves)
        
        # Choose best move
        valid_policy = {m: policy[m] for m in valid_moves}
        best_move = max(valid_policy, key=valid_policy.get)
        
        return best_move
    
    def print_board(self, game):
        """Print the board with move indices"""
        print("\n  0 | 1 | 2")
        print(" -----------")
        print("  3 | 4 | 5")
        print(" -----------")
        print("  6 | 7 | 8\n")
        
        print("Current board:")
        print(game.get_board_string())
        print()
    
    def play(self, human_first=True):
        """Play a game against the human"""
        game = TicTacToe()
        
        print("=" * 40)
        print("Tic-Tac-Toe vs Neural Network")
        print("=" * 40)
        print("\nYou are X, the AI is O")
        if not human_first:
            print("AI goes first!")
        
        while not game.game_over:
            self.print_board(game)
            
            if (game.current_player == Player.X and human_first) or \
               (game.current_player == Player.O and not human_first):
                # Human's turn
                valid_moves = game.get_valid_moves()
                print(f"Valid moves: {valid_moves}")
                
                try:
                    move = int(input("Enter your move (0-8): "))
                    if move not in valid_moves:
                        print("Invalid move! Try again.")
                        continue
                except ValueError:
                    print("Please enter a number between 0 and 8.")
                    continue
                
                valid, reward = game.make_move(move)
                if not valid:
                    print("Invalid move! Try again.")
                    continue
                
            else:
                # AI's turn
                print("AI is thinking...")
                move = self.get_model_move(game)
                
                if move is not None:
                    row, col = move // 3, move % 3
                    print(f"AI plays move {move} (row {row}, col {col})")
                    game.make_move(move)
                else:
                    print("No valid moves for AI!")
                    break
        
        # Game over
        self.print_board(game)
        
        if game.winner == Player.X:
            print("🎉 You win!")
        elif game.winner == Player.O:
            print("🤖 AI wins!")
        else:
            print("🤝 It's a draw!")
        
        return game.winner


def main():
    player = GamePlayer()
    
    while True:
        # Ask who goes first
        first = input("\nDo you want to go first? (y/n): ").lower().strip()
        human_first = first == 'y' or first == 'yes'
        
        player.play(human_first=human_first)
        
        # Ask to play again
        again = input("\nPlay again? (y/n): ").lower().strip()
        if again != 'y' and again != 'yes':
            break
    
    print("\nThanks for playing!")


if __name__ == '__main__':
    main()

