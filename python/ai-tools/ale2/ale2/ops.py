import math
import random


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


def linear(x, w, b):
    """y = x @ w + b. x is (m, n), w is (n, p), b has length p."""
    return [[v + b[j] for j, v in enumerate(row)] for row in matmul(x, w)]


def transpose(a):
    return [[a[i][j] for i in range(len(a))] for j in range(len(a[0]))]


def linear_backward(x, w, dy):
    """Gradients of y = x @ w + b. Returns dx, dw, db."""
    db = [sum(row[j] for row in dy) for j in range(len(dy[0]))]
    dw = matmul(transpose(x), dy)
    dx = matmul(dy, transpose(w))
    return dx, dw, db


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


def cross_entropy_backward(logits, targets):
    """Gradient of mean cross-entropy w.r.t. logits. Same shape as logits."""
    if len(logits) != len(targets):
        raise ValueError("logits and targets must have the same batch size")
    if not targets:
        raise ValueError("targets must be non-empty")
    n = len(targets)
    dlogits = [[p / n for p in row] for row in softmax(logits)]
    for i, t in enumerate(targets):
        dlogits[i][t] -= 1 / n
    return dlogits


def sgd_step(w, b, dw, db, lr):
    """In-place update: w -= lr * dw, b -= lr * db."""
    for i, row in enumerate(w):
        for j, value in enumerate(row):
            row[j] = value - lr * dw[i][j]
    for j, value in enumerate(b):
        b[j] = value - lr * db[j]


def adamw_step(param, grad, moment, velocity, lr, step, beta1=0.9, beta2=0.999, eps=1e-8, wd=0.01):
    """In-place AdamW. step starts at 1. moment and velocity match param and are updated."""
    if param and isinstance(param[0], list):
        for p, g, m, v in zip(param, grad, moment, velocity):
            adamw_step(p, g, m, v, lr, step, beta1, beta2, eps, wd)
        return
    bias1 = 1.0 - beta1 ** step
    bias2 = 1.0 - beta2 ** step
    for j, value in enumerate(param):
        moment[j] = beta1 * moment[j] + (1.0 - beta1) * grad[j]
        velocity[j] = beta2 * velocity[j] + (1.0 - beta2) * grad[j] * grad[j]
        mhat = moment[j] / bias1
        vhat = velocity[j] / bias2
        param[j] = value - lr * (mhat / (math.sqrt(vhat) + eps) + wd * value)


def greedy(logits_row):
    """Index of the largest logit. The first index wins a tie."""
    return max(range(len(logits_row)), key=logits_row.__getitem__)


def sample(logits, temperature=1.0, top_k=None, rng=None):
    """Draw one index from softmax(logits / temperature), optionally restricted to top_k."""
    if rng is None:
        rng = random
    scaled = [v / max(temperature, 1e-8) for v in logits]
    if top_k is not None and top_k < len(scaled):
        cutoff = sorted(scaled, reverse=True)[top_k - 1]
        scaled = [v if v >= cutoff else float("-inf") for v in scaled]
    probs = softmax([scaled])[0]
    return rng.choices(range(len(probs)), weights=probs, k=1)[0]


def causal_mask(length):
    """Lower triangle, diagonal included. Entry (i, j) is 1 when j <= i."""
    return [[1 if j <= i else 0 for j in range(length)] for i in range(length)]


def attention_scores(q, k):
    """Scaled q @ k.T with future positions set to -inf. q and k are (T, head_dim)."""
    scale = 1.0 / math.sqrt(len(q[0]))
    raw = matmul(q, transpose(k))
    mask = causal_mask(len(q))
    return [
        [value * scale if keep else float("-inf") for value, keep in zip(row, mask_row)]
        for row, mask_row in zip(raw, mask)
    ]


def attend(q, k, v):
    """Softmax over attention scores, then a weighted sum of v."""
    return matmul(softmax(attention_scores(q, k)), v)


def attend_backward(q, k, v, dy):
    """Gradients of attend. Returns dq, dk, dv."""
    scale = 1.0 / math.sqrt(len(q[0]))
    weights = softmax(attention_scores(q, k))
    dweights = matmul(dy, transpose(v))
    dscores = []
    for weight_row, grad_row in zip(weights, dweights):
        dot = sum(weight * grad for weight, grad in zip(weight_row, grad_row))
        dscores.append([weight * (grad - dot) for weight, grad in zip(weight_row, grad_row)])
    mask = causal_mask(len(q))
    draw = [
        [grad * scale if keep else 0.0 for grad, keep in zip(row, mask_row)]
        for row, mask_row in zip(dscores, mask)
    ]
    dq = matmul(draw, k)
    dk = matmul(transpose(draw), q)
    dv = matmul(transpose(weights), dy)
    return dq, dk, dv


def qkv(x, w, b):
    """Project each token into query, key, and value. Output width is 3 * head_dim."""
    projected = linear(x, w, b)
    width = len(projected[0])
    if width % 3 != 0:
        raise ValueError("qkv output width must be divisible by 3")
    part = width // 3
    q = [row[:part] for row in projected]
    k = [row[part : 2 * part] for row in projected]
    v = [row[2 * part :] for row in projected]
    return q, k, v


def split_heads(rows, n_head):
    """Split the last dimension into n_head contiguous pieces."""
    width = len(rows[0])
    if n_head < 1 or width % n_head != 0:
        raise ValueError("width must be divisible by n_head")
    head_dim = width // n_head
    return [
        [row[h * head_dim:(h + 1) * head_dim] for row in rows]
        for h in range(n_head)
    ]


def merge_heads(heads):
    """Concatenate head rows back into one width."""
    return [
        [value for head in heads for value in head[t]]
        for t in range(len(heads[0]))
    ]


def self_attention(x, w_qkv, b_qkv, w_out, b_out, n_head=1):
    """Causal attention over n_head pieces of each token, then project back."""
    queries, keys, values = qkv(x, w_qkv, b_qkv)
    mixed = merge_heads([
        attend(q, k, v)
        for q, k, v in zip(split_heads(queries, n_head), split_heads(keys, n_head), split_heads(values, n_head))
    ])
    return linear(mixed, w_out, b_out)


def self_attention_backward(x, w_qkv, b_qkv, w_out, b_out, dy, n_head=1):
    """Gradients of self_attention. Returns dx, dw_qkv, db_qkv, dw_out, db_out."""
    queries, keys, values = qkv(x, w_qkv, b_qkv)
    q_heads = split_heads(queries, n_head)
    k_heads = split_heads(keys, n_head)
    v_heads = split_heads(values, n_head)
    mixed = merge_heads([
        attend(q, k, v) for q, k, v in zip(q_heads, k_heads, v_heads)
    ])
    d_mixed, dw_out, db_out = linear_backward(mixed, w_out, dy)
    dq_heads, dk_heads, dv_heads = [], [], []
    for q, k, v, d_head in zip(q_heads, k_heads, v_heads, split_heads(d_mixed, n_head)):
        dq, dk, dv = attend_backward(q, k, v, d_head)
        dq_heads.append(dq)
        dk_heads.append(dk)
        dv_heads.append(dv)
    dq, dk, dv = merge_heads(dq_heads), merge_heads(dk_heads), merge_heads(dv_heads)
    d_projected = [dq_row + dk_row + dv_row for dq_row, dk_row, dv_row in zip(dq, dk, dv)]
    dx, dw_qkv, db_qkv = linear_backward(x, w_qkv, d_projected)
    return dx, dw_qkv, db_qkv, dw_out, db_out


def add(a, b):
    """Elementwise sum of two matrices with the same shape."""
    return [[ai + bi for ai, bi in zip(row_a, row_b)] for row_a, row_b in zip(a, b)]


def layer_norm(x, gamma, beta, eps=1e-5):
    """Normalize each row, then apply gamma and beta. Variance divides by the row length."""
    out = []
    for row in x:
        n = len(row)
        mean = sum(row) / n
        var = sum((v - mean) ** 2 for v in row) / n
        scale = math.sqrt(var + eps)
        out.append([gamma[j] * (v - mean) / scale + beta[j] for j, v in enumerate(row)])
    return out


def layer_norm_backward(x, gamma, dy, eps=1e-5):
    """Gradients of layer norm. Returns dx, dgamma, dbeta."""
    dgamma = [0.0] * len(gamma)
    dbeta = [0.0] * len(gamma)
    dx = []
    for row, drow in zip(x, dy):
        n = len(row)
        mean = sum(row) / n
        var = sum((v - mean) ** 2 for v in row) / n
        std = math.sqrt(var + eps)
        xhat = [(v - mean) / std for v in row]
        for j in range(n):
            dgamma[j] += drow[j] * xhat[j]
            dbeta[j] += drow[j]
        dxhat = [drow[j] * gamma[j] for j in range(n)]
        mean_dx = sum(dxhat) / n
        mean_dx_xhat = sum(a * b for a, b in zip(dxhat, xhat)) / n
        dx.append([(dxhat[j] - mean_dx - xhat[j] * mean_dx_xhat) / std for j in range(n)])
    return dx, dgamma, dbeta


def gelu(x):
    """Exact GELU, matching torch.nn.GELU: 0.5 * v * (1 + erf(v / sqrt(2)))."""
    root = math.sqrt(2.0)
    return [[0.5 * v * (1.0 + math.erf(v / root)) for v in row] for row in x]


def gelu_backward(x, dy):
    """Gradient of exact GELU. dy has the same shape as x."""
    root = math.sqrt(2.0)
    inv_sqrt_2pi = 1.0 / math.sqrt(2.0 * math.pi)
    out = []
    for row, drow in zip(x, dy):
        grad = []
        for value, upstream in zip(row, drow):
            local = 0.5 * (1.0 + math.erf(value / root))
            local += value * math.exp(-0.5 * value * value) * inv_sqrt_2pi
            grad.append(upstream * local)
        out.append(grad)
    return out


def mlp(x, w1, b1, w2, b2):
    """linear, GELU, linear. w1 maps to the hidden width, w2 maps back."""
    return linear(gelu(linear(x, w1, b1)), w2, b2)


def mlp_backward(x, w1, b1, w2, b2, dy):
    """Gradients of mlp. Returns dx, dw1, db1, dw2, db2."""
    hidden = linear(x, w1, b1)
    activated = gelu(hidden)
    d_activated, dw2, db2 = linear_backward(activated, w2, dy)
    d_hidden = gelu_backward(hidden, d_activated)
    dx, dw1, db1 = linear_backward(x, w1, d_hidden)
    return dx, dw1, db1, dw2, db2


def block(x, ln1_gamma, ln1_beta, w_qkv, b_qkv, w_out, b_out, ln2_gamma, ln2_beta, w1, b1, w2, b2, n_head=1):
    """x + attention(layer_norm(x)), then x + mlp(layer_norm(x))."""
    attended = self_attention(layer_norm(x, ln1_gamma, ln1_beta), w_qkv, b_qkv, w_out, b_out, n_head)
    x = add(x, attended)
    return add(x, mlp(layer_norm(x, ln2_gamma, ln2_beta), w1, b1, w2, b2))


def block_backward(x, ln1_gamma, ln1_beta, w_qkv, b_qkv, w_out, b_out, ln2_gamma, ln2_beta, w1, b1, w2, b2, dy, n_head=1):
    """Gradients of block, in the same parameter order as block, preceded by dx."""
    hidden1 = layer_norm(x, ln1_gamma, ln1_beta)
    attended = self_attention(hidden1, w_qkv, b_qkv, w_out, b_out, n_head)
    mid = add(x, attended)
    hidden2 = layer_norm(mid, ln2_gamma, ln2_beta)
    d_hidden2, dw1, db1, dw2, db2 = mlp_backward(hidden2, w1, b1, w2, b2, dy)
    d_mid_norm, dln2_gamma, dln2_beta = layer_norm_backward(mid, ln2_gamma, d_hidden2)
    d_mid = add(dy, d_mid_norm)
    d_hidden1, dw_qkv, db_qkv, dw_out, db_out = self_attention_backward(
        hidden1, w_qkv, b_qkv, w_out, b_out, d_mid, n_head
    )
    d_x_norm, dln1_gamma, dln1_beta = layer_norm_backward(x, ln1_gamma, d_hidden1)
    dx = add(d_mid, d_x_norm)
    return (
        dx,
        dln1_gamma, dln1_beta,
        dw_qkv, db_qkv, dw_out, db_out,
        dln2_gamma, dln2_beta,
        dw1, db1, dw2, db2,
    )


def gpt_forward(
    ids,
    token_table,
    pos_table,
    blocks,
    ln_f_gamma, ln_f_beta,
    w_head, b_head,
    n_head=1,
):
    """Token plus position, each block, final layer norm, then vocabulary logits."""
    x = add_position(embed(token_table, ids), pos_table)
    for block_params in blocks:
        x = block(x, *block_params, n_head=n_head)
    return linear(layer_norm(x, ln_f_gamma, ln_f_beta), w_head, b_head)


def gpt_backward(
    ids,
    token_table,
    pos_table,
    blocks,
    ln_f_gamma, ln_f_beta,
    w_head, b_head,
    dy,
    n_head=1,
):
    """Gradients of gpt_forward. block gradients are in forward order, without dx."""
    x = add_position(embed(token_table, ids), pos_table)
    block_inputs = []
    for block_params in blocks:
        block_inputs.append(x)
        x = block(x, *block_params, n_head=n_head)
    normed = layer_norm(x, ln_f_gamma, ln_f_beta)
    d_normed, dw_head, db_head = linear_backward(normed, w_head, dy)
    dx, dln_f_gamma, dln_f_beta = layer_norm_backward(x, ln_f_gamma, d_normed)
    block_grads = []
    for block_input, block_params in zip(reversed(block_inputs), reversed(blocks)):
        grads = block_backward(block_input, *block_params, dx, n_head)
        dx = grads[0]
        block_grads.append(grads[1:])
    block_grads.reverse()
    d_token = embed_backward(token_table, ids, dx)
    d_pos = embed_backward(pos_table, range(len(ids)), dx)
    return d_token, d_pos, block_grads, dln_f_gamma, dln_f_beta, dw_head, db_head


def residual_attention(x, w_qkv, b_qkv, w_out, b_out):
    """x + self_attention(x)."""
    return add(x, self_attention(x, w_qkv, b_qkv, w_out, b_out))


def embed(table, ids):
    """Look up a copy of each row. table is (vocab, n), ids is a list of ints."""
    return [table[i][:] for i in ids]


def add_position(token_rows, pos_table):
    """Add position rows 0..T-1 onto token rows of length T."""
    return add(token_rows, embed(pos_table, range(len(token_rows))))


def embed_backward(table, ids, dy):
    """Scatter dy into a zero gradient of the same shape as table. Repeated ids add."""
    dw = [[0.0] * len(table[0]) for _ in table]
    for i, idx in enumerate(ids):
        for j, grad in enumerate(dy[i]):
            dw[idx][j] += grad
    return dw
