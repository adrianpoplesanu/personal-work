"""Generate text from a trained character-level GPT checkpoint."""

from __future__ import annotations

import argparse
from pathlib import Path

import torch

from ale1.config import SampleConfig, TrainConfig
from ale1.model import GPT
from ale1.tokenizer import CharTokenizer
from ale1.train import pick_device


def load_model(checkpoint_dir: Path, device: torch.device) -> tuple[GPT, CharTokenizer]:
    tok_path = checkpoint_dir / "tokenizer.json"
    model_path = checkpoint_dir / "model.pt"
    if not tok_path.exists() or not model_path.exists():
        raise FileNotFoundError(
            f"missing checkpoint files in {checkpoint_dir} "
            "(expected tokenizer.json and model.pt). Run train.py first."
        )

    tokenizer = CharTokenizer.load(tok_path)
    ckpt = torch.load(model_path, map_location=device, weights_only=False)
    cfg_dict = ckpt["config"]
    train_config = TrainConfig(**{k: cfg_dict[k] for k in TrainConfig.__dataclass_fields__ if k in cfg_dict})
    model = GPT(ckpt["vocab_size"], train_config)
    model.load_state_dict(ckpt["model_state"])
    model.to(device)
    model.eval()
    return model, tokenizer


def generate(
    model: GPT,
    tokenizer: CharTokenizer,
    prompt: str,
    max_new_tokens: int,
    temperature: float,
    top_k: int | None,
    device: torch.device,
) -> str:
    if not prompt:
        # seed with a newline or first vocab char so generation can start
        prompt = "\n" if "\n" in tokenizer.stoi else tokenizer.chars[0]
    idx = torch.tensor([tokenizer.encode(prompt)], dtype=torch.long, device=device)
    out = model.generate(idx, max_new_tokens=max_new_tokens, temperature=temperature, top_k=top_k)
    return tokenizer.decode(out[0].tolist())


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--checkpoint-dir", default=SampleConfig.checkpoint_dir)
    parser.add_argument("--prompt", default=SampleConfig.prompt)
    parser.add_argument("--max-new-tokens", type=int, default=SampleConfig.max_new_tokens)
    parser.add_argument("--temperature", type=float, default=SampleConfig.temperature)
    parser.add_argument("--top-k", type=int, default=SampleConfig.top_k)
    parser.add_argument("--no-top-k", action="store_true", help="disable top-k filtering")
    parser.add_argument("--seed", type=int, default=SampleConfig.seed)
    parser.add_argument(
        "--device",
        default="auto",
        choices=["auto", "cpu", "cuda", "mps"],
    )
    args = parser.parse_args()

    torch.manual_seed(args.seed)
    device = pick_device(args.device)
    top_k = None if args.no_top_k else args.top_k

    model, tokenizer = load_model(Path(args.checkpoint_dir), device)
    text = generate(
        model,
        tokenizer,
        prompt=args.prompt,
        max_new_tokens=args.max_new_tokens,
        temperature=args.temperature,
        top_k=top_k,
        device=device,
    )
    print(text)


if __name__ == "__main__":
    main()
