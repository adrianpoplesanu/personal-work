import torch


if __name__ == "__main__":
    mat1 = torch.ones(4, 3)
    mat2 = torch.ones(3, 4)
    mat3 = torch.matmul(mat1, mat2)
    print(mat3)

    a = torch.zeros(3, 5)
    b = torch.zeros(3, 5)
    c = torch.multiply(a, b)
    print(c)
