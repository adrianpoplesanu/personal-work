from dataclasses import dataclass


@dataclass
class TrainConfig:
    """Hyperparameters for a small educational GPT."""

    data_path: str = "data/tiny.txt"
    checkpoint_dir: str = "checkpoints"
    block_size: int = 64
    n_embd: int = 128
    n_layer: int = 4
    n_head: int = 4
    dropout: float = 0.1
    batch_size: int = 32
    learning_rate: float = 3e-4
    max_steps: int = 2000
    eval_interval: int = 200
    seed: int = 42
    device: str = "cpu"  # set to "cuda" or "mps" when available


@dataclass
class SampleConfig:
    """Defaults for text generation."""

    checkpoint_dir: str = "checkpoints"
    prompt: str = "To be"
    max_new_tokens: int = 200
    temperature: float = 0.8
    top_k: int | None = 40
    seed: int = 42
    device: str = "cpu"
