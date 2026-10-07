"""Tests for pure-Python ops."""

from __future__ import annotations

import math

import pytest

from ale2.ops import cross_entropy, log_softmax, matmul, softmax


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
