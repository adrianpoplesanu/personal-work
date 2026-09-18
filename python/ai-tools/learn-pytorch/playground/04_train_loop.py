"""Minimal train loop: Module + loss + optimizer — end-to-end syntax check."""

from __future__ import annotations

import torch
import torch.nn as nn
from torch.utils.data import DataLoader, TensorDataset


class Regressor(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(1, 32),
            nn.Tanh(),
            nn.Linear(32, 1),
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.net(x)


def make_toy_data(n: int = 256) -> DataLoader:
    # y = 2x + 1 + noise
    x = torch.linspace(-1, 1, n).unsqueeze(1)
    y = 2 * x + 1 + 0.1 * torch.randn_like(x)
    ds = TensorDataset(x, y)
    return DataLoader(ds, batch_size=32, shuffle=True)


def train(epochs: int = 20) -> None:
    device = torch.device("cpu")
    model = Regressor().to(device)
    opt = torch.optim.Adam(model.parameters(), lr=1e-2)
    loss_fn = nn.MSELoss()
    loader = make_toy_data()

    model.train()
    for epoch in range(1, epochs + 1):
        total = 0.0
        for xb, yb in loader:
            xb, yb = xb.to(device), yb.to(device)
            pred = model(xb)
            loss = loss_fn(pred, yb)

            opt.zero_grad(set_to_none=True)
            loss.backward()
            opt.step()
            total += loss.item() * xb.size(0)

        if epoch == 1 or epoch % 5 == 0 or epoch == epochs:
            print(f"epoch {epoch:02d}  loss={total / len(loader.dataset):.4f}")

    model.eval()
    with torch.no_grad():
        probe = torch.tensor([[0.0], [0.5], [1.0]])
        print("preds @ 0 / 0.5 / 1:", model(probe).squeeze().tolist())


if __name__ == "__main__":
    train()
