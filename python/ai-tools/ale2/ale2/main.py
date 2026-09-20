"""Entry point for ale2."""
from pathlib import Path

from ale2.config import Config
from ale2.tokenizer import CharTokenizer


def main() -> None:
    config = Config()
    tokenizer = CharTokenizer.from_text("ale2 is ready")
    ckpt_dir = Path(config.checkpoint_path)
    tokenizer.save(ckpt_dir / "tokenizer.json")


if __name__ == "__main__":
    main()
