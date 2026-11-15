"""Tests for pure-Python ops."""

from __future__ import annotations

import math
import random

import pytest

from ale2.ops import (
    adamw_step,
    add,
    add_position,
    attend,
    attend_backward,
    attention_scores,
    block,
    block_backward,
    causal_mask,
    cross_entropy,
    cross_entropy_backward,
    embed,
    embed_backward,
    gelu,
    gelu_backward,
    gpt_backward,
    gpt_forward,
    greedy,
    residual_attention,
    sample,
    layer_norm,
    layer_norm_backward,
    linear,
    linear_backward,
    qkv,
    self_attention,
    self_attention_backward,
    log_softmax,
    mlp,
    mlp_backward,
    matmul,
    sgd_step,
    softmax,
)


def test_softmax_sums_to_one() -> None:
    probs = softmax([[1.0, 2.0, 3.0]])[0]
    assert abs(sum(probs) - 1.0) < 1e-12
    assert all(p > 0 for p in probs)


def test_log_softmax_matches_log_of_softmax() -> None:
    logits = [[1.0, 2.0, 3.0], [-1.0, 0.0, 5.0]]
    log_probs = log_softmax(logits)
    probs = softmax(logits)
    for lp_row, p_row in zip(log_probs, probs):
        for lp, p in zip(lp_row, p_row):
            assert abs(lp - math.log(p)) < 1e-12


def test_matmul() -> None:
    a = [[1, 2], [3, 4]]
    b = [[5, 6], [7, 8]]
    assert matmul(a, b) == [[19, 22], [43, 50]]

def test_matmul_broadcast() -> None:
    a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    b = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    assert matmul(a, b) == [[30, 36, 42], [66, 81, 96], [102, 126, 150]]


def test_matmul_non_square() -> None:
    assert matmul([[1, 2, 3]], [[1], [2], [3]]) == [[14]]


def test_linear_adds_bias() -> None:
    x = [[1, 0], [0, 1]]
    w = [[1, 2], [3, 4]]
    b = [10, 20]
    assert linear(x, w, b) == [[11, 22], [13, 24]]


def test_linear_backward() -> None:
    x = [[1, 2], [3, 4]]
    w = [[1, 0], [0, 1]]
    dy = [[1, 1], [1, 1]]
    dx, dw, db = linear_backward(x, w, dy)
    assert db == [2, 2]
    assert dw == [[4, 4], [6, 6]]
    assert dx == [[1, 1], [1, 1]]

def test_cross_entropy_prefers_correct_class() -> None:
    logits = [[5.0, 0.0, 0.0]]
    assert cross_entropy(logits, [0]) < cross_entropy(logits, [1])
    assert cross_entropy(logits, [0]) < 0.1


def test_cross_entropy_batch_mean() -> None:
    logits = [[10.0, 0.0], [0.0, 10.0]]
    loss = cross_entropy(logits, [0, 1])
    assert loss < 0.01


def test_cross_entropy_mismatched_batch_raises() -> None:
    with pytest.raises(ValueError, match="same batch size"):
        cross_entropy([[1.0, 2.0]], [0, 1])


def test_cross_entropy_backward() -> None:
    dlogits = cross_entropy_backward([[2.0, 0.0]], [0])
    total = 1.0 + math.exp(-2.0)
    expected = [1.0 / total - 1.0, math.exp(-2.0) / total]
    assert abs(dlogits[0][0] - expected[0]) < 1e-12
    assert abs(dlogits[0][1] - expected[1]) < 1e-12


def test_adamw_step_matches_one_update() -> None:
    param = [1.0, 2.0]
    moment = [0.0, 0.0]
    velocity = [0.0, 0.0]
    adamw_step(param, [0.5, -1.0], moment, velocity, lr=0.1, step=1, wd=0.0)
    assert abs(param[0] - 0.9) < 1e-6
    assert abs(param[1] - 2.1) < 1e-6


def test_sgd_step() -> None:
    w = [[1.0, 2.0]]
    b = [3.0]
    sgd_step(w, b, [[0.5, -1.0]], [4.0], lr=0.5)
    assert w == [[0.75, 2.5]]
    assert b == [1.0]


def test_sgd_lowers_loss() -> None:
    x = [[1.0, 0.0], [0.0, 1.0]]
    targets = [0, 1]
    w = [[0.0, 0.0], [0.0, 0.0]]
    b = [0.0, 0.0]
    first = cross_entropy(linear(x, w, b), targets)
    for _ in range(50):
        logits = linear(x, w, b)
        dy = cross_entropy_backward(logits, targets)
        _, dw, db = linear_backward(x, w, dy)
        sgd_step(w, b, dw, db, lr=0.1)
    last = cross_entropy(linear(x, w, b), targets)
    assert last < first


def test_greedy_picks_largest_logit() -> None:
    assert greedy([0.1, 3.0, 2.0]) == 1
    assert greedy([1.0, 1.0, 0.0]) == 0


def test_causal_mask_hides_the_future() -> None:
    assert causal_mask(3) == [
        [1, 0, 0],
        [1, 1, 0],
        [1, 1, 1],
    ]


def test_attention_scores_scale_and_mask() -> None:
    q = [[1.0, 0.0], [0.0, 1.0]]
    k = [[1.0, 0.0], [0.0, 1.0]]
    scale = 1.0 / math.sqrt(2.0)
    scores = attention_scores(q, k)
    assert scores[0][1] == float("-inf")
    assert abs(scores[0][0] - scale) < 1e-12
    assert abs(scores[1][0] - 0.0) < 1e-12
    assert abs(scores[1][1] - scale) < 1e-12


def test_attend_mixes_only_the_past() -> None:
    q = [[1.0, 0.0], [0.0, 1.0]]
    k = [[1.0, 0.0], [0.0, 1.0]]
    v = [[10.0, 20.0], [30.0, 40.0]]
    out = attend(q, k, v)
    assert out[0] == [10.0, 20.0]
    scale = 1.0 / math.sqrt(2.0)
    past = math.exp(-scale)
    total = past + 1.0
    p0, p1 = past / total, 1.0 / total
    assert abs(out[1][0] - (p0 * 10.0 + p1 * 30.0)) < 1e-12
    assert abs(out[1][1] - (p0 * 20.0 + p1 * 40.0)) < 1e-12


def _dot(rows, weights) -> float:
    return sum(value * weight for row, grow in zip(rows, weights) for value, weight in zip(row, grow))


def test_attend_backward_matches_finite_difference() -> None:
    q = [[0.2, -0.1], [0.4, 0.3]]
    k = [[0.5, 0.1], [-0.2, 0.2]]
    v = [[1.0, 0.0], [0.0, 1.0]]
    dy = [[0.3, -0.4], [0.5, 0.2]]
    dq, dk, dv = attend_backward(q, k, v, dy)
    eps = 1e-5

    def loss(qq, kk, vv):
        return _dot(attend(qq, kk, vv), dy)

    for param, grad, slot in ((q, dq, "q"), (k, dk, "k"), (v, dv, "v")):
        for i, row in enumerate(param):
            for j, value in enumerate(row):
                plus = [list(item) for item in param]
                minus = [list(item) for item in param]
                plus[i][j] = value + eps
                minus[i][j] = value - eps
                args = {"q": (plus, k, v), "k": (q, plus, v), "v": (q, k, plus)}[slot]
                args_minus = {"q": (minus, k, v), "k": (q, minus, v), "v": (q, k, minus)}[slot]
                approx = (loss(*args) - loss(*args_minus)) / (2 * eps)
                assert abs(grad[i][j] - approx) < 1e-5


def test_self_attention_backward_matches_finite_difference() -> None:
    x = [[0.2, -0.1], [0.4, 0.3]]
    w_qkv = [
        [0.1, 0.0, 0.2, 0.0, 0.3, 0.0],
        [0.0, 0.1, 0.0, -0.2, 0.0, 0.4],
    ]
    b_qkv = [0.0] * 6
    w_out = [[0.5, -0.1], [0.2, 0.3]]
    b_out = [0.0, 0.0]
    dy = [[0.3, -0.2], [0.1, 0.4]]
    _, dw_qkv, _, dw_out, _ = self_attention_backward(x, w_qkv, b_qkv, w_out, b_out, dy)
    eps = 1e-5

    def loss(qkv_w, out_w):
        return _dot(self_attention(x, qkv_w, b_qkv, out_w, b_out), dy)

    for i, j in ((0, 0), (1, 4)):
        plus = [row[:] for row in w_qkv]
        minus = [row[:] for row in w_qkv]
        plus[i][j] += eps
        minus[i][j] -= eps
        approx = (loss(plus, w_out) - loss(minus, w_out)) / (2 * eps)
        assert abs(dw_qkv[i][j] - approx) < 1e-5
    plus = [row[:] for row in w_out]
    minus = [row[:] for row in w_out]
    plus[0][1] += eps
    minus[0][1] -= eps
    approx = (loss(w_qkv, plus) - loss(w_qkv, minus)) / (2 * eps)
    assert abs(dw_out[0][1] - approx) < 1e-5


def test_two_heads_backward_matches_finite_difference() -> None:
    x = [[0.2, -0.1, 0.3, 0.0], [0.4, 0.3, -0.2, 0.1]]
    w_qkv = [[0.05 * ((i + 1) + (j + 1)) for j in range(12)] for i in range(4)]
    b_qkv = [0.0] * 12
    w_out = [[0.1 if i == j else 0.0 for j in range(4)] for i in range(4)]
    b_out = [0.0] * 4
    dy = [[0.2, -0.1, 0.0, 0.3], [0.1, 0.2, -0.2, 0.0]]
    _, dw_qkv, _, dw_out, _ = self_attention_backward(
        x, w_qkv, b_qkv, w_out, b_out, dy, n_head=2
    )
    out = self_attention(x, w_qkv, b_qkv, w_out, b_out, n_head=2)
    assert len(out[0]) == len(x[0])
    eps = 1e-5

    def loss(qkv_w, out_w):
        return _dot(self_attention(x, qkv_w, b_qkv, out_w, b_out, n_head=2), dy)

    plus = [row[:] for row in w_qkv]
    minus = [row[:] for row in w_qkv]
    plus[0][3] += eps
    minus[0][3] -= eps
    approx = (loss(plus, w_out) - loss(minus, w_out)) / (2 * eps)
    assert abs(dw_qkv[0][3] - approx) < 1e-4
    plus_o = [row[:] for row in w_out]
    minus_o = [row[:] for row in w_out]
    plus_o[1][2] += eps
    minus_o[1][2] -= eps
    approx = (loss(w_qkv, plus_o) - loss(w_qkv, minus_o)) / (2 * eps)
    assert abs(dw_out[1][2] - approx) < 1e-4


def test_qkv_splits_projection_into_three() -> None:
    x = [[0.0, 0.0], [0.0, 0.0]]
    w = [[0.0] * 6, [0.0] * 6]
    b = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    queries, keys, values = qkv(x, w, b)
    assert queries == [[1.0, 2.0], [1.0, 2.0]]
    assert keys == [[3.0, 4.0], [3.0, 4.0]]
    assert values == [[5.0, 6.0], [5.0, 6.0]]


def test_self_attention_hides_future_values() -> None:
    x = [[1.0, 0.0], [0.0, 1.0]]
    w_qkv = [
        [1.0, 0.0, 1.0, 0.0, 10.0, 20.0],
        [0.0, 1.0, 0.0, 1.0, 30.0, 40.0],
    ]
    b_qkv = [0.0] * 6
    w_out = [[1.0, 0.0], [0.0, 1.0]]
    b_out = [0.0, 0.0]
    out = self_attention(x, w_qkv, b_qkv, w_out, b_out)
    assert out[0] == [10.0, 20.0]
    scale = 1.0 / math.sqrt(2.0)
    past = math.exp(-scale)
    total = past + 1.0
    p0, p1 = past / total, 1.0 / total
    assert abs(out[1][0] - (p0 * 10.0 + p1 * 30.0)) < 1e-12
    assert abs(out[1][1] - (p0 * 20.0 + p1 * 40.0)) < 1e-12


def test_residual_attention_adds_output_onto_x() -> None:
    x = [[1.0, 0.0], [0.0, 1.0]]
    w_qkv = [
        [1.0, 0.0, 1.0, 0.0, 10.0, 20.0],
        [0.0, 1.0, 0.0, 1.0, 30.0, 40.0],
    ]
    b_qkv = [0.0] * 6
    w_out = [[1.0, 0.0], [0.0, 1.0]]
    b_out = [0.0, 0.0]
    out = residual_attention(x, w_qkv, b_qkv, w_out, b_out)
    assert out[0] == [11.0, 20.0]
    scale = 1.0 / math.sqrt(2.0)
    past = math.exp(-scale)
    total = past + 1.0
    p0, p1 = past / total, 1.0 / total
    assert abs(out[1][0] - (p0 * 10.0 + p1 * 30.0)) < 1e-12
    assert abs(out[1][1] - (1.0 + p0 * 20.0 + p1 * 40.0)) < 1e-12


def test_sample_top_k_keeps_only_the_largest() -> None:
    rng = random.Random(0)
    picks = {sample([1.0, 2.0, 10.0], top_k=1, rng=rng) for _ in range(20)}
    assert picks == {2}


def test_sample_top_k_two_drops_the_smallest() -> None:
    rng = random.Random(0)
    picks = {sample([1.0, 5.0, 4.0], top_k=2, rng=rng) for _ in range(30)}
    assert 0 not in picks


def test_gelu_matches_erf_formula() -> None:
    value = 1.0
    expected = 0.5 * value * (1.0 + math.erf(value / math.sqrt(2.0)))
    assert abs(gelu([[value, 0.0, -value]])[0][0] - expected) < 1e-12
    assert gelu([[value, 0.0, -value]])[0][1] == 0.0
    assert gelu([[value, 0.0, -value]])[0][2] < 0.0


def test_gelu_backward_matches_finite_difference() -> None:
    assert gelu_backward([[0.0]], [[2.0]]) == [[1.0]]
    row = [0.5, -1.0, 2.0]
    analytic = gelu_backward([row], [[1.0, 1.0, 1.0]])[0]
    eps = 1e-5
    for value, grad in zip(row, analytic):
        plus = gelu([[value + eps]])[0][0]
        minus = gelu([[value - eps]])[0][0]
        assert abs(grad - (plus - minus) / (2 * eps)) < 1e-6


def test_mlp_applies_gelu_between_linears() -> None:
    hidden = gelu([[1.0, -1.0]])[0]
    out = mlp(
        [[0.0, 0.0]],
        w1=[[0.0, 0.0], [0.0, 0.0]],
        b1=[1.0, -1.0],
        w2=[[1.0, 0.0], [0.0, 1.0]],
        b2=[0.0, 0.0],
    )
    assert abs(out[0][0] - hidden[0]) < 1e-12
    assert abs(out[0][1] - hidden[1]) < 1e-12


def test_block_adds_attention_and_mlp_residuals() -> None:
    x = [[1.0, 3.0]]
    gamma = [1.0, 1.0]
    beta = [0.0, 0.0]
    eye = [[1.0, 0.0], [0.0, 1.0]]
    out = block(
        x,
        gamma, beta,
        [[0.0] * 6, [0.0] * 6], [0.0] * 6,
        [[0.0, 0.0], [0.0, 0.0]], [0.0, 0.0],
        gamma, beta,
        eye, [0.0, 0.0],
        eye, [0.0, 0.0],
    )
    scale = math.sqrt(1.0 + 1e-5)
    normed = gelu([[-1.0 / scale, 1.0 / scale]])[0]
    assert abs(out[0][0] - (1.0 + normed[0])) < 1e-12
    assert abs(out[0][1] - (3.0 + normed[1])) < 1e-12


def test_block_backward_matches_finite_difference() -> None:
    x = [[0.2, -0.4], [0.5, 0.1]]
    ln1_gamma = [1.0, 0.8]
    ln1_beta = [0.0, 0.1]
    w_qkv = [
        [0.1, 0.0, 0.2, 0.0, 0.3, 0.0],
        [0.0, 0.1, 0.0, -0.2, 0.0, 0.4],
    ]
    b_qkv = [0.0] * 6
    w_out = [[0.2, -0.1], [0.1, 0.3]]
    b_out = [0.0, 0.05]
    ln2_gamma = [0.9, 1.1]
    ln2_beta = [0.0, -0.1]
    w1 = [[0.4, -0.2], [0.1, 0.3]]
    b1 = [0.0, 0.1]
    w2 = [[0.2, 0.1], [-0.3, 0.4]]
    b2 = [0.0, 0.0]
    dy = [[0.3, -0.2], [0.1, 0.4]]
    (
        dx, dln1_gamma, _, dw_qkv, _, dw_out, _, _, dln2_beta, dw1, _, dw2, _,
    ) = block_backward(
        x, ln1_gamma, ln1_beta, w_qkv, b_qkv, w_out, b_out,
        ln2_gamma, ln2_beta, w1, b1, w2, b2, dy,
    )
    eps = 1e-5

    def loss(xx, g1, qkv_w, out_w, b2_ln, first_w, second_w):
        y = block(
            xx, g1, ln1_beta, qkv_w, b_qkv, out_w, b_out,
            ln2_gamma, b2_ln, first_w, b1, second_w, b2,
        )
        return _dot(y, dy)

    def approx(changed, other):
        return (loss(*changed) - loss(*other)) / (2 * eps)

    plus_x = [row[:] for row in x]
    minus_x = [row[:] for row in x]
    plus_x[0][1] += eps
    minus_x[0][1] -= eps
    assert abs(dx[0][1] - approx((plus_x, ln1_gamma, w_qkv, w_out, ln2_beta, w1, w2), (minus_x, ln1_gamma, w_qkv, w_out, ln2_beta, w1, w2))) < 1e-4

    plus_g = ln1_gamma[:]
    minus_g = ln1_gamma[:]
    plus_g[0] += eps
    minus_g[0] -= eps
    assert abs(dln1_gamma[0] - approx((x, plus_g, w_qkv, w_out, ln2_beta, w1, w2), (x, minus_g, w_qkv, w_out, ln2_beta, w1, w2))) < 1e-4

    plus_q = [row[:] for row in w_qkv]
    minus_q = [row[:] for row in w_qkv]
    plus_q[1][4] += eps
    minus_q[1][4] -= eps
    assert abs(dw_qkv[1][4] - approx((x, ln1_gamma, plus_q, w_out, ln2_beta, w1, w2), (x, ln1_gamma, minus_q, w_out, ln2_beta, w1, w2))) < 1e-4

    plus_o = [row[:] for row in w_out]
    minus_o = [row[:] for row in w_out]
    plus_o[0][1] += eps
    minus_o[0][1] -= eps
    assert abs(dw_out[0][1] - approx((x, ln1_gamma, w_qkv, plus_o, ln2_beta, w1, w2), (x, ln1_gamma, w_qkv, minus_o, ln2_beta, w1, w2))) < 1e-4

    plus_b = ln2_beta[:]
    minus_b = ln2_beta[:]
    plus_b[1] += eps
    minus_b[1] -= eps
    assert abs(dln2_beta[1] - approx((x, ln1_gamma, w_qkv, w_out, plus_b, w1, w2), (x, ln1_gamma, w_qkv, w_out, minus_b, w1, w2))) < 1e-4

    plus_1 = [row[:] for row in w1]
    minus_1 = [row[:] for row in w1]
    plus_1[0][1] += eps
    minus_1[0][1] -= eps
    assert abs(dw1[0][1] - approx((x, ln1_gamma, w_qkv, w_out, ln2_beta, plus_1, w2), (x, ln1_gamma, w_qkv, w_out, ln2_beta, minus_1, w2))) < 1e-4

    plus_2 = [row[:] for row in w2]
    minus_2 = [row[:] for row in w2]
    plus_2[1][0] += eps
    minus_2[1][0] -= eps
    assert abs(dw2[1][0] - approx((x, ln1_gamma, w_qkv, w_out, ln2_beta, w1, plus_2), (x, ln1_gamma, w_qkv, w_out, ln2_beta, w1, minus_2))) < 1e-4


def test_gpt_forward_logits_depend_on_position() -> None:
    ids = [0, 0]
    token_table = [[1.0, 3.0]]
    pos_table = [[10.0, 0.0], [0.0, 10.0]]
    gamma = [1.0, 1.0]
    beta = [0.0, 0.0]
    eye = [[1.0, 0.0], [0.0, 1.0]]
    block_params = (
        gamma, beta,
        [[0.0] * 6, [0.0] * 6], [0.0] * 6,
        [[0.0, 0.0], [0.0, 0.0]], [0.0, 0.0],
        gamma, beta,
        eye, [0.0, 0.0],
        eye, [0.0, 0.0],
    )
    logits = gpt_forward(
        ids, token_table, pos_table, [block_params], gamma, beta, eye, [0.0, 0.0],
    )
    x = add(add_position(embed(token_table, ids), pos_table), gelu(layer_norm(
        add_position(embed(token_table, ids), pos_table), gamma, beta
    )))
    expected = layer_norm(x, gamma, beta)
    assert logits[0] != logits[1]
    for row, target in zip(logits, expected):
        assert abs(row[0] - target[0]) < 1e-12
        assert abs(row[1] - target[1]) < 1e-12


def test_gpt_backward_reaches_embeddings_and_attention() -> None:
    ids = [0, 0]
    token_table = [[0.2, -0.1], [0.4, 0.3]]
    pos_table = [[0.1, 0.0], [-0.2, 0.2]]
    ln1_gamma = [1.0, 0.8]
    ln1_beta = [0.0, 0.1]
    w_qkv = [
        [0.1, 0.0, 0.2, 0.0, 0.3, 0.0],
        [0.0, 0.1, 0.0, -0.2, 0.0, 0.4],
    ]
    b_qkv = [0.0] * 6
    w_out = [[0.2, -0.1], [0.1, 0.3]]
    b_out = [0.0, 0.05]
    ln2_gamma = [0.9, 1.1]
    ln2_beta = [0.0, -0.1]
    w1 = [[0.4, -0.2], [0.1, 0.3]]
    b1 = [0.0, 0.1]
    w2 = [[0.2, 0.1], [-0.3, 0.4]]
    b2 = [0.0, 0.0]
    ln_f_gamma = [1.0, 1.0]
    ln_f_beta = [0.0, 0.0]
    w_head = [[0.5, -0.2], [0.1, 0.4]]
    b_head = [0.0, 0.0]
    dy = [[0.3, -0.2], [0.1, 0.4]]

    def blocks_with(qkv_w):
        return [(
            ln1_gamma, ln1_beta, qkv_w, b_qkv, w_out, b_out,
            ln2_gamma, ln2_beta, w1, b1, w2, b2,
        )]

    d_token, d_pos, block_grads, _, _, dw_head, _ = gpt_backward(
        ids, token_table, pos_table, blocks_with(w_qkv),
        ln_f_gamma, ln_f_beta, w_head, b_head, dy,
    )
    dw_qkv = block_grads[0][2]
    eps = 1e-5

    def loss(tokens, positions, qkv_w, head_w):
        logits = gpt_forward(
            ids, tokens, positions, blocks_with(qkv_w),
            ln_f_gamma, ln_f_beta, head_w, b_head,
        )
        return _dot(logits, dy)

    plus_token = [row[:] for row in token_table]
    minus_token = [row[:] for row in token_table]
    plus_token[0][0] += eps
    minus_token[0][0] -= eps
    token_approx = (loss(plus_token, pos_table, w_qkv, w_head) - loss(minus_token, pos_table, w_qkv, w_head)) / (2 * eps)
    assert abs(d_token[0][0] - token_approx) < 1e-4

    plus_pos = [row[:] for row in pos_table]
    minus_pos = [row[:] for row in pos_table]
    plus_pos[1][0] += eps
    minus_pos[1][0] -= eps
    pos_approx = (loss(token_table, plus_pos, w_qkv, w_head) - loss(token_table, minus_pos, w_qkv, w_head)) / (2 * eps)
    assert abs(d_pos[1][0] - pos_approx) < 1e-4

    plus_q = [row[:] for row in w_qkv]
    minus_q = [row[:] for row in w_qkv]
    plus_q[0][0] += eps
    minus_q[0][0] -= eps
    qkv_approx = (loss(token_table, pos_table, plus_q, w_head) - loss(token_table, pos_table, minus_q, w_head)) / (2 * eps)
    assert abs(dw_qkv[0][0] - qkv_approx) < 1e-4

    plus_head = [row[:] for row in w_head]
    minus_head = [row[:] for row in w_head]
    plus_head[0][1] += eps
    minus_head[0][1] -= eps
    head_approx = (loss(token_table, pos_table, w_qkv, plus_head) - loss(token_table, pos_table, w_qkv, minus_head)) / (2 * eps)
    assert abs(dw_head[0][1] - head_approx) < 1e-4


def test_layer_norm_centers_and_scales() -> None:
    scale = math.sqrt(1.0 + 1e-5)
    out = layer_norm([[1.0, 3.0]], gamma=[2.0, 2.0], beta=[10.0, 20.0])
    assert abs(out[0][0] - (10.0 - 2.0 / scale)) < 1e-12
    assert abs(out[0][1] - (20.0 + 2.0 / scale)) < 1e-12


def test_layer_norm_backward_matches_finite_difference() -> None:
    row = [1.0, 3.0, 2.0]
    gamma = [1.0, 0.5, 2.0]
    beta = [0.2, -0.3, 0.4]
    dy = [0.3, -0.2, 0.7]
    dx, dgamma, dbeta = layer_norm_backward([row], gamma, [dy])
    assert dbeta == dy
    eps = 1e-5

    def dot(values):
        y = layer_norm([values], gamma, beta)[0]
        return sum(a * b for a, b in zip(y, dy))

    for j, value in enumerate(row):
        plus = row[:]
        minus = row[:]
        plus[j] += eps
        minus[j] -= eps
        approx = (dot(plus) - dot(minus)) / (2 * eps)
        assert abs(dx[0][j] - approx) < 1e-6
    for j, value in enumerate(gamma):
        plus = gamma[:]
        minus = gamma[:]
        plus[j] += eps
        minus[j] -= eps
        plus_loss = sum(a * b for a, b in zip(layer_norm([row], plus, beta)[0], dy))
        minus_loss = sum(a * b for a, b in zip(layer_norm([row], minus, beta)[0], dy))
        assert abs(dgamma[j] - (plus_loss - minus_loss) / (2 * eps)) < 1e-6


def test_add_position_shifts_the_same_token() -> None:
    tokens = [[1.0, 2.0], [1.0, 2.0]]
    pos_table = [[10.0, 20.0], [30.0, 40.0]]
    assert add_position(tokens, pos_table) == [[11.0, 22.0], [31.0, 42.0]]


def test_embed_copies_rows() -> None:
    table = [[1, 2], [3, 4], [5, 6]]
    out = embed(table, [2, 0, 2])
    assert out == [[5, 6], [1, 2], [5, 6]]
    out[0][0] = 0
    assert table[2][0] == 5


def test_embed_backward_scatters_and_adds() -> None:
    table = [[1, 2], [3, 4], [5, 6]]
    dy = [[1, 0], [0, 1], [1, 1]]
    dw = embed_backward(table, [2, 0, 2], dy)
    assert dw[0] == [0, 1]
    assert dw[1] == [0, 0]
    assert dw[2] == [2, 1]


def test_embed_linear_lowers_loss() -> None:
    ids = [0, 1]
    targets = [0, 1]
    table = [[0.0, 0.0], [0.0, 0.0]]
    w = [[1.0, 0.0], [0.0, 1.0]]
    b = [0.0, 0.0]
    first = cross_entropy(linear(embed(table, ids), w, b), targets)
    for _ in range(50):
        x = embed(table, ids)
        logits = linear(x, w, b)
        dy = cross_entropy_backward(logits, targets)
        dx, dw, db = linear_backward(x, w, dy)
        dtable = embed_backward(table, ids, dx)
        sgd_step(w, b, dw, db, lr=0.1)
        sgd_step(table, [], dtable, [], lr=0.1)
    last = cross_entropy(linear(embed(table, ids), w, b), targets)
    assert last < first
