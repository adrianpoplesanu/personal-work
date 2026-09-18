"""Tensor creation, shapes, indexing, broadcasting, and autograd basics."""

from __future__ import annotations

import torch


def tensor_basics() -> None:
    x = torch.tensor([[1.0, 2.0], [3.0, 4.0]])
    y = torch.zeros(2, 3)
    z = torch.randn(4, 5)  # N(0, 1)
    ones = torch.ones_like(x)

    print("x:", x, "shape=", x.shape, "dtype=", x.dtype)
    print("y:", y.shape, "z:", z.shape, "ones:", ones)

    # Views / reshape (same storage when possible)
    flat = x.view(-1)
    reshaped = x.reshape(1, 4)
    print("flat:", flat, "reshaped:", reshaped)

    # Indexing / slicing
    print("x[0, 1] =", x[0, 1].item())
    print("x[:, 0] =", x[:, 0])


def broadcasting_and_ops() -> None:
    a = torch.arange(3).float()  # (3,)
    b = torch.ones(2, 3)  # (2, 3)
    print("broadcast a+b:", a + b)

    # Elementwise vs matmul
    m = torch.randn(2, 3)
    n = torch.randn(3, 4)
    print("matmul:", m @ n)
    print("elementwise *:", m * m)

    # Reductions
    print("sum=", m.sum().item(), "mean=", m.mean().item(), "max=", m.max().item())


def autograd_basics() -> None:
    w = torch.tensor(2.0, requires_grad=True)
    b = torch.tensor(1.0, requires_grad=True)
    x = torch.tensor(3.0)

    # y = w*x + b  -> dy/dw = x, dy/db = 1
    y = w * x + b
    y.backward()
    print("y =", y.item(), "w.grad =", w.grad, "b.grad =", b.grad)

    # Clear grads before another backward
    w.grad.zero_()
    b.grad.zero_()


def device_and_dtype() -> None:
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    t = torch.randn(2, 2, dtype=torch.float32, device=device)
    print("device:", device, "tensor device:", t.device)
    if device.type == "cpu":
        print("(MPS available:" , torch.backends.mps.is_available(), ")")


if __name__ == "__main__":
    print("=== tensor_basics ===")
    tensor_basics()
    print("\n=== broadcasting_and_ops ===")
    broadcasting_and_ops()
    print("\n=== autograd_basics ===")
    autograd_basics()
    print("\n=== device_and_dtype ===")
    device_and_dtype()
