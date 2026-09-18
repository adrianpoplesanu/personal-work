"""torch.nn modules, parameters, Sequential, and a tiny custom Module."""

from __future__ import annotations

import torch
import torch.nn as nn
import torch.nn.functional as F


class TinyMLP(nn.Module):
    def __init__(self, in_dim: int, hidden: int, out_dim: int) -> None:
        super().__init__()
        self.fc1 = nn.Linear(in_dim, hidden)
        self.fc2 = nn.Linear(hidden, out_dim)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = F.relu(self.fc1(x))
        return self.fc2(x)


def module_inventory() -> None:
    # Common building blocks — create, inspect shapes, don't train yet
    linear = nn.Linear(4, 8)
    conv = nn.Conv2d(in_channels=1, out_channels=16, kernel_size=3, padding=1)
    emb = nn.Embedding(num_embeddings=100, embedding_dim=32)
    drop = nn.Dropout(p=0.1)
    bn = nn.BatchNorm1d(8)
    ln = nn.LayerNorm(8)

    x = torch.randn(2, 4)
    print("Linear:", linear(x).shape)
    print("Embedding:", emb(torch.tensor([1, 2, 3])).shape)

    img = torch.randn(2, 1, 28, 28)
    print("Conv2d:", conv(img).shape)

    h = torch.randn(2, 8)
    print("BatchNorm1d:", bn(h).shape, "LayerNorm:", ln(h).shape)
    print("Dropout (train):", drop(h).shape)

    # Sequential composition
    net = nn.Sequential(
        nn.Linear(4, 16),
        nn.ReLU(),
        nn.Linear(16, 3),
    )
    print("Sequential:", net(x).shape)


def custom_module_and_params() -> None:
    model = TinyMLP(in_dim=4, hidden=16, out_dim=3)
    x = torch.randn(8, 4)
    logits = model(x)
    print("TinyMLP out:", logits.shape)

    # Parameters are registered tensors with requires_grad=True
    n_params = sum(p.numel() for p in model.parameters())
    n_trainable = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print(f"params={n_params}, trainable={n_trainable}")

    for name, p in model.named_parameters():
        print(f"  {name}: {tuple(p.shape)}")


def loss_and_functional() -> None:
    logits = torch.randn(4, 3, requires_grad=True)
    targets = torch.tensor([0, 2, 1, 0])

    loss_ce = F.cross_entropy(logits, targets)
    loss_mse = F.mse_loss(torch.randn(4, 3), torch.randn(4, 3))
    print("cross_entropy:", loss_ce.item(), "mse:", loss_mse.item())

    # Softmax / log_softmax along class dim
    probs = F.softmax(logits, dim=-1)
    print("softmax sum (should be ~1):", probs.sum(dim=-1))


if __name__ == "__main__":
    print("=== module_inventory ===")
    module_inventory()
    print("\n=== custom_module_and_params ===")
    custom_module_and_params()
    print("\n=== loss_and_functional ===")
    loss_and_functional()
