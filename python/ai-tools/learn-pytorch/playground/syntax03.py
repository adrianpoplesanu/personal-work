import torch

if __name__ == "__main__":
    x = torch.randn(4, 4)
    print(torch.sort(x, dim=1))