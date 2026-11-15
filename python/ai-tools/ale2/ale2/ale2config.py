from dataclasses import dataclass


@dataclass
class Ale2Config:
    data_path: str = "data/source.txt"
    checkpoint_path: str = "checkpoints"
    device: str = "cpu" # other values: cuda or mps
    block_size: int = 64
    batch_size: int = 32
    n_embd: int = 16
    n_head: int = 4
    n_layer: int = 1
    learning_rate: float = 0.05
    weight_decay: float = 0.01
    max_steps: int = 200
    seed: int = 42
