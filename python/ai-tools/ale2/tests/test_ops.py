"""Tests for pure-Python ops."""

from __future__ import annotations

import math

import pytest

from ale2.ops import cross_entropy, log_softmax, softmax


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
