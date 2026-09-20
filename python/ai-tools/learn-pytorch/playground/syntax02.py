import torch

if __name__ == "__main__":
    a = torch.randn(3, 3)
    print(a)
    print(torch.abs(a))

    print(torch.softmax(a, dim=0))

    print(torch.softmax(a, dim=1))
