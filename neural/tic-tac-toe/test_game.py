"""
Simple test script to verify the game works correctly
"""
from game import TicTacToe, Player

def test_game():
    game = TicTacToe()
    
    # Test a simple game
    print("Testing tic-tac-toe game...")
    print("\nInitial board:")
    print(game.get_board_string())
    
    # Make some moves
    moves = [0, 1, 3, 4, 6]  # X wins with diagonal
    
    for move in moves:
        print(f"\nMove {move}:")
        valid, reward = game.make_move(move)
        print(f"Valid: {valid}, Reward: {reward}")
        print(game.get_board_string())
        print(f"Game over: {game.game_over}, Winner: {game.winner}")
        
        if game.game_over:
            break
    
    print("\nTest complete!")

if __name__ == '__main__':
    test_game()

