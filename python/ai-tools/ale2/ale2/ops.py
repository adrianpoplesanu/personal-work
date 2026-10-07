import math


def softmax(x):
    out = []
    for row in x:
        m = max(row)
        exps = [math.exp(v - m) for v in row]
        total = sum(exps)
        out.append([e / total for e in exps])
    return out


def log_softmax(x):
    out = []
    for row in x:
        m = max(row)
        exps = [math.exp(v - m) for v in row]
        log_sum = math.log(sum(exps))
        out.append([v - m - log_sum for v in row])
    return out


def matmul(a, b):
    n = len(b)
    p = len(b[0])
    return [
        [sum(a[i][k] * b[k][j] for k in range(n)) for j in range(p)]
        for i in range(len(a))
    ]


def cross_entropy(logits, targets):
    """Mean negative log-likelihood over a batch of rows.

    logits: list of rows (each a list of class scores)
    targets: list of integer class indices, one per row
    """
    if len(logits) != len(targets):
        raise ValueError("logits and targets must have the same batch size")
    if not targets:
        raise ValueError("targets must be non-empty")
    log_probs = log_softmax(logits)
    losses = [-row[t] for row, t in zip(log_probs, targets)]
    return sum(losses) / len(losses)
