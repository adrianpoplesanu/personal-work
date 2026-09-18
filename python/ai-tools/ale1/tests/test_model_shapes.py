"""Shape and smoke tests for the GPT model."""

from __future__ import annotations

import torch

from ale1.config import TrainConfig
from ale1.model import GPT


def test_forward_shapes() -> None:
    config = TrainConfig(
        block_size=16,
        n_embd=32,
        n_layer=2,
        n_head=4,
        dropout=0.0,
        batch_size=4,
    )
    vocab_size = 20
    model = GPT(vocab_size, config)
    B, T = 4, 16
    idx = torch.randint(0, vocab_size, (B, T))
    targets = torch.randint(0, vocab_size, (B, T))
    logits, loss = model(idx, targets)
    assert logits.shape == (B, T, vocab_size)
    assert loss is not None
    assert loss.ndim == 0


def test_generate_extends_sequence() -> None:
    config = TrainConfig(
        block_size=8,
        n_embd=32,
        n_layer=1,
        n_head=4,
        dropout=0.0,
    )
    vocab_size = 10
    model = GPT(vocab_size, config)
    model.eval()
    idx = torch.randint(0, vocab_size, (1, 3))
    out = model.generate(idx, max_new_tokens=5, temperature=1.0, top_k=5)
    assert out.shape == (1, 8)
