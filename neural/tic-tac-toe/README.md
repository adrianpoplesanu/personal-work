# Neural Network Tic-Tac-Toe Player

A neural network that learns to play tic-tac-toe through self-play training using PyTorch.

## Overview

This project implements a neural network that learns to play tic-tac-toe using a self-play reinforcement learning approach. The network uses a value-policy architecture similar to AlphaZero, where:
- **Value head**: Predicts the probability of winning from the current position
- **Policy head**: Predicts the probability distribution over all possible moves

## Project Structure

```
.
├── game.py          # Tic-tac-toe game environment
├── model.py         # Neural network architecture
├── train.py         # Training script with self-play
├── play.py          # Interactive game against trained model
├── requirements.txt # Python dependencies
└── README.md        # This file
```

## Installation

1. Install Python 3.8 or higher

2. Install dependencies:
```bash
pip install -r requirements.txt
```

## Usage

### Training the Model

Train the neural network using self-play:

```bash
python train.py
```

The training script will:
- Play self-play games where the model plays against itself
- Collect training data from these games
- Train the model using value and policy losses
- Save the trained model to `models/tic_tac_toe_model.pth`

You can modify training parameters in `train.py`:
- `num_games`: Total number of self-play games (default: 500)
- `games_per_batch`: Number of games before training step (default: 10)
- `epsilon`: Exploration rate (default: 0.3)
- `lr`: Learning rate (default: 0.001)

### Playing Against the Model

After training, play against the AI:

```bash
python play.py
```

The game will:
- Load the trained model (or use untrained model if not found)
- Let you choose to go first or second
- Display the board with move indices (0-8)
- Show the AI's moves and predictions

### Move Indices

The board positions are numbered as follows:
```
0 | 1 | 2
-----------
3 | 4 | 5
-----------
6 | 7 | 8
```

## How It Works

### Game Environment (`game.py`)
- Implements the tic-tac-toe game logic
- Tracks game state, valid moves, and win conditions
- Provides methods for making moves and checking game status

### Neural Network (`model.py`)
- **Architecture**: 3-layer fully connected network with 128 hidden units
- **Input**: 9 values (flattened 3x3 board state)
- **Outputs**:
  - Value: Single probability (0-1) of winning
  - Policy: 9 values representing move probabilities

### Training (`train.py`)
- **Self-Play**: Model plays against itself to generate training data
- **Exploration**: Uses epsilon-greedy exploration with temperature sampling
- **Loss Functions**:
  - Value loss: MSE between predicted and actual game outcome
  - Policy loss: Cross-entropy between predicted and actual moves
- **Memory Buffer**: Stores game states for batch training

### Playing (`play.py`)
- Interactive command-line interface
- Loads trained model and plays against human player
- Shows board state and move predictions

## Training Tips

1. **More Games = Better Performance**: Increase `num_games` for better results (try 1000-5000)
2. **Adjust Learning Rate**: Lower learning rates (0.0001) may be more stable for longer training
3. **Exploration**: Higher epsilon values (0.3-0.5) help exploration early in training
4. **Batch Size**: Larger batch sizes (64-128) can stabilize training

## Example Training Output

```
Starting training on cpu...
Total games: 500, Games per batch: 10
Game 10/500 - Loss: 0.8234 (Value: 0.4123, Policy: 0.4111) Epsilon: 0.299 Memory: 120
Game 20/500 - Loss: 0.7123 (Value: 0.3456, Policy: 0.3667) Epsilon: 0.298 Memory: 240
...
Training complete!
Model saved to models/tic_tac_toe_model.pth
```

## Future Improvements

- Add Monte Carlo Tree Search (MCTS) for better move selection
- Implement curriculum learning (start with simpler positions)
- Add evaluation metrics (win rate against random player)
- Visualize training progress with plots
- Support for different board sizes
- GUI interface instead of command-line

## License

This project is open source and available for educational purposes.

