def accept(a, n, k):
    return not a[k] in a[0:k]

def back(a, n, k):
    if k == n:
        print a
    else:
        a[k] = 0
        while a[k] < n:
            if accept(a, n, k):
                back(a, n, k + 1)
            a[k] += 1

def run():
    n = 3
    a = [0 for i in range(n)]
    back(a, n, 0)

if __name__ == '__main__':
    run()
