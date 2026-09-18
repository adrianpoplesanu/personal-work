"""Train a tiny character-level GPT."""

from __future__ import annotations

import argparse
from pathlib import Path

import torch
from tqdm import tqdm

from ale1.config import TrainConfig
from ale1.model import GPT
from ale1.tokenizer import CharTokenizer


def pick_device(requested: str) -> torch.device:
    if requested == "cuda" and torch.cuda.is_available():
        return torch.device("cuda")
    if requested == "mps" and getattr(torch.backends, "mps", None) and torch.backends.mps.is_available():
        return torch.device("mps")
    if requested == "auto":
        if torch.cuda.is_available():
            return torch.device("cuda")
        if getattr(torch.backends, "mps", None) and torch.backends.mps.is_available():
            return torch.device("mps")
        return torch.device("cpu")
    return torch.device("cpu")


def get_batch(
    data: torch.Tensor,
    batch_size: int,
    block_size: int,
    device: torch.device,
) -> tuple[torch.Tensor, torch.Tensor]:
    max_start = data.size(0) - block_size - 1
    ix = torch.randint(0, max_start + 1, (batch_size,))
    x = torch.stack([data[i : i + block_size] for i in ix])
    y = torch.stack([data[i + 1 : i + block_size + 1] for i in ix])
    return x.to(device), y.to(device)


def train(config: TrainConfig) -> None:
    torch.manual_seed(config.seed)
    device = pick_device(config.device)

    text = Path(config.data_path).read_text(encoding="utf-8")
    tokenizer = CharTokenizer.from_text(text)
    data = torch.tensor(tokenizer.encode(text), dtype=torch.long)

    if data.size(0) <= config.block_size + 1:
        raise ValueError(
            f"corpus too short ({data.size(0)} tokens) for block_size={config.block_size}"
        )

    model = GPT(tokenizer.vocab_size, config).to(device)
    optimizer = torch.optim.AdamW(model.parameters(), lr=config.learning_rate)

    ckpt_dir = Path(config.checkpoint_dir)
    ckpt_dir.mkdir(parents=True, exist_ok=True)

    print(
        f"device={device} | vocab={tokenizer.vocab_size} | "
        f"params={sum(p.numel() for p in model.parameters()):,} | "
        f"tokens={data.size(0):,}"
    )

    model.train()
    pbar = tqdm(range(1, config.max_steps + 1), desc="train")
    for step in pbar:
        xb, yb = get_batch(data, config.batch_size, config.block_size, device)
        _, loss = model(xb, yb)
        optimizer.zero_grad(set_to_none=True)
        loss.backward()
        optimizer.step()

        if step % config.eval_interval == 0 or step == 1:
            pbar.set_postfix(loss=f"{loss.item():.4f}")

    tokenizer.save(ckpt_dir / "tokenizer.json")
    torch.save(
        {
            "model_state": model.state_dict(),
            "config": config.__dict__,
            "vocab_size": tokenizer.vocab_size,
        },
        ckpt_dir / "model.pt",
    )
    print(f"saved checkpoint to {ckpt_dir}/")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--data", default=TrainConfig.data_path)
    parser.add_argument("--checkpoint-dir", default=TrainConfig.checkpoint_dir)
    parser.add_argument("--block-size", type=int, default=TrainConfig.block_size)
    parser.add_argument("--n-embd", type=int, default=TrainConfig.n_embd)
    parser.add_argument("--n-layer", type=int, default=TrainConfig.n_layer)
    parser.add_argument("--n-head", type=int, default=TrainConfig.n_head)
    parser.add_argument("--dropout", type=float, default=TrainConfig.dropout)
    parser.add_argument("--batch-size", type=int, default=TrainConfig.batch_size)
    parser.add_argument("--lr", type=float, default=TrainConfig.learning_rate)
    parser.add_argument("--max-steps", type=int, default=TrainConfig.max_steps)
    parser.add_argument("--eval-interval", type=int, default=TrainConfig.eval_interval)
    parser.add_argument("--seed", type=int, default=TrainConfig.seed)
    parser.add_argument(
        "--device",
        default="auto",
        choices=["auto", "cpu", "cuda", "mps"],
        help="compute device (auto picks cuda/mps/cpu)",
    )
    args = parser.parse_args()

    config = TrainConfig(
        data_path=args.data,
        checkpoint_dir=args.checkpoint_dir,
        block_size=args.block_size,
        n_embd=args.n_embd,
        n_layer=args.n_layer,
        n_head=args.n_head,
        dropout=args.dropout,
        batch_size=args.batch_size,
        learning_rate=args.lr,
        max_steps=args.max_steps,
        eval_interval=args.eval_interval,
        seed=args.seed,
        device=args.device,
    )
    train(config)


if __name__ == "__main__":
    main()
