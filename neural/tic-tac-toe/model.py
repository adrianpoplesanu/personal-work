"""
Neural network model for tic-tac-toe
"""
import torch
import torch.nn as nn
import torch.nn.functional as F


class TicTacToeNet(nn.Module):
    """
    Neural network that takes board state and outputs:
    - Value: probability of winning from current position
    - Policy: probability distribution over all moves
    """
    def __init__(self, hidden_size=128):
        super(TicTacToeNet, self).__init__()
        
        # Input: 9 values (flattened 3x3 board)
        self.fc1 = nn.Linear(9, hidden_size)
        self.fc2 = nn.Linear(hidden_size, hidden_size)
        self.fc3 = nn.Linear(hidden_size, hidden_size)
        
        # Value head: outputs single value (win probability)
        self.value_head = nn.Linear(hidden_size, 1)
        
        # Policy head: outputs 9 values (one for each move)
        self.policy_head = nn.Linear(hidden_size, 9)
        
        self.dropout = nn.Dropout(0.1)
    
    def forward(self, x):
        """
        Forward pass
        Args:
            x: board state (batch_size, 9) or (9,)
        Returns:
            value: (batch_size, 1) or (1,)
            policy: (batch_size, 9) or (9,)
        """
        # Ensure input is 2D
        if x.dim() == 1:
            x = x.unsqueeze(0)
        
        x = F.relu(self.fc1(x))
        x = self.dropout(x)
        x = F.relu(self.fc2(x))
        x = self.dropout(x)
        x = F.relu(self.fc3(x))
        
        # Value output (sigmoid to get probability between 0 and 1)
        value = torch.sigmoid(self.value_head(x))
        
        # Policy output (logits, will be masked and softmaxed during training)
        policy = self.policy_head(x)
        
        return value.squeeze(-1), policy.squeeze(0) if policy.dim() == 2 and policy.size(0) == 1 else policy
    
    def predict(self, board_state, valid_moves):
        """
        Predict value and policy for a given board state
        Args:
            board_state: numpy array of shape (9,)
            valid_moves: list of valid move indices
        Returns:
            value: float, predicted win probability
            policy: numpy array of shape (9,), probability distribution over moves
        """
        self.eval()
        with torch.no_grad():
            # Convert to tensor and normalize
            state_tensor = torch.FloatTensor(board_state).unsqueeze(0)
            
            value, policy_logits = self.forward(state_tensor)
            
            # Mask invalid moves
            policy_mask = torch.zeros(9)
            for move in valid_moves:
                policy_mask[move] = 1.0
            
            # Apply mask and softmax
            masked_policy = policy_logits * policy_mask - (1 - policy_mask) * 1e9
            policy_probs = F.softmax(masked_policy, dim=-1)
            
            return value.item(), policy_probs.numpy()

