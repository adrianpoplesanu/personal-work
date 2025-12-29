"""
Tic-Tac-Toe game environment
"""
import numpy as np
from typing import List, Tuple, Optional
from enum import Enum


class Player(Enum):
    X = 1
    O = -1
    EMPTY = 0


class TicTacToe:
    def __init__(self):
        self.board = np.zeros((3, 3), dtype=int)
        self.current_player = Player.X
        self.game_over = False
        self.winner = None
        self.move_history = []
    
    def reset(self):
        """Reset the game to initial state"""
        self.board = np.zeros((3, 3), dtype=int)
        self.current_player = Player.X
        self.game_over = False
        self.winner = None
        self.move_history = []
        return self.get_state()
    
    def get_state(self) -> np.ndarray:
        """Get current board state as a flattened array"""
        return self.board.flatten().copy()
    
    def get_valid_moves(self) -> List[int]:
        """Get list of valid move indices (0-8)"""
        valid_moves = []
        for i in range(9):
            row, col = i // 3, i % 3
            if self.board[row, col] == Player.EMPTY.value:
                valid_moves.append(i)
        return valid_moves
    
    def make_move(self, move: int) -> Tuple[bool, Optional[int]]:
        """
        Make a move on the board
        Returns: (valid_move, reward)
        - valid_move: True if move was valid, False otherwise
        - reward: 1 if win, 0 if draw, -1 if loss, None if game continues
        """
        if self.game_over:
            return False, None
        
        if move not in self.get_valid_moves():
            return False, None
        
        row, col = move // 3, move % 3
        self.board[row, col] = self.current_player.value
        self.move_history.append(move)
        
        # Check for win
        if self._check_win(row, col):
            self.game_over = True
            self.winner = self.current_player
            reward = 1  # Current player wins
            return True, reward
        
        # Check for draw
        if len(self.get_valid_moves()) == 0:
            self.game_over = True
            self.winner = None
            reward = 0  # Draw
            return True, reward
        
        # Switch player
        self.current_player = Player.O if self.current_player == Player.X else Player.X
        return True, None
    
    def _check_win(self, row: int, col: int) -> bool:
        """Check if the last move resulted in a win"""
        player_value = self.board[row, col]
        
        # Check row
        if np.all(self.board[row, :] == player_value):
            return True
        
        # Check column
        if np.all(self.board[:, col] == player_value):
            return True
        
        # Check diagonals
        if row == col and np.all(np.diag(self.board) == player_value):
            return True
        
        if row + col == 2 and np.all(np.diag(np.fliplr(self.board)) == player_value):
            return True
        
        return False
    
    def get_board_string(self) -> str:
        """Get a string representation of the board"""
        symbols = {Player.X.value: 'X', Player.O.value: 'O', Player.EMPTY.value: ' '}
        lines = []
        for i in range(3):
            row = [symbols[self.board[i, j]] for j in range(3)]
            lines.append(' | '.join(row))
        return '\n---------\n'.join(lines)
    
    def copy(self):
        """Create a deep copy of the game state"""
        new_game = TicTacToe()
        new_game.board = self.board.copy()
        new_game.current_player = self.current_player
        new_game.game_over = self.game_over
        new_game.winner = self.winner
        new_game.move_history = self.move_history.copy()
        return new_game

