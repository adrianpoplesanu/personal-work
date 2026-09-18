"""stdlib math vs torch math — when to use which in model code."""

from __future__ import annotations

import math

import torch
import torch.nn as nn


def stdlib_math_scalars() -> None:
    # Use for config, schedules, and Python scalars (not batched tensors)
    lr = 1e-3
    warmup = 100
    step = 50
    # cosine-ish schedule fragment
    progress = step / warmup
    scale = 0.5 * (1.0 + math.cos(math.pi * progress))
    print("scalar schedule scale:", scale, "sqrt(2):", math.sqrt(2), "log:", math.log(lr))


def torch_math_on_tensors() -> None:
    x = torch.linspace(-math.pi, math.pi, steps=5)
    print("x:", x)
    print("sin:", torch.sin(x))
    print("exp:", torch.exp(x))
    print("log1p:", torch.log1p(torch.tensor([0.0, 0.5, 1.0])))
    print("clamp:", torch.clamp(x, min=-1.0, max=1.0))

    # Numerically safer patterns common in models
    logits = torch.randn(2, 4)
    log_sum_exp = torch.logsumexp(logits, dim=-1)
    print("logsumexp:", log_sum_exp)


def attention_scale_example() -> None:
    """Classic QK^T / sqrt(d_k) scaling uses math.sqrt (scalar) or tensor ops."""
    d_k = 64
    scale = 1.0 / math.sqrt(d_k)  # Python float — fine for a constant

    q = torch.randn(2, 8, d_k)  # (batch, seq, dim)
    k = torch.randn(2, 8, d_k)
    scores = (q @ k.transpose(-2, -1)) * scale
    weights = torch.softmax(scores, dim=-1)
    print("attn weights shape:", weights.shape, "row sum ~1:", weights.sum(dim=-1)[0, 0].item())


class PositionalEncoding(nn.Module):
    """sin/cos PE — mixes math.pi with torch tensor math."""

    def __init__(self, d_model: int, max_len: int = 64) -> None:
        super().__init__()
        pe = torch.zeros(max_len, d_model)
        position = torch.arange(0, max_len, dtype=torch.float32).unsqueeze(1)
        div_term = torch.exp(
            torch.arange(0, d_model, 2, dtype=torch.float32)
            * (-math.log(10000.0) / d_model)
        )
        pe[:, 0::2] = torch.sin(position * div_term)
        pe[:, 1::2] = torch.cos(position * div_term)
        self.register_buffer("pe", pe.unsqueeze(0))  # (1, max_len, d_model)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        # x: (batch, seq, d_model)
        return x + self.pe[:, : x.size(1)]


if __name__ == "__main__":
    print("=== stdlib_math_scalars ===")
    stdlib_math_scalars()
    print("\n=== torch_math_on_tensors ===")
    torch_math_on_tensors()
    print("\n=== attention_scale_example ===")
    attention_scale_example()
    print("\n=== PositionalEncoding ===")
    pe = PositionalEncoding(d_model=16, max_len=32)
    out = pe(torch.randn(2, 10, 16))
    print("PE out:", out.shape)
