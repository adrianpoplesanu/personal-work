from dataclasses import dataclass


@dataclass
class Config:
    data_path: str = "data/source.txt"
    checkpoint_path: str = "checkpoints"
    device: str = "cpu" # other values: cuda or mps
