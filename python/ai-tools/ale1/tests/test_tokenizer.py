"""Tests for CharTokenizer."""

from __future__ import annotations

from pathlib import Path

import pytest

from ale1.tokenizer import CharTokenizer


def test_round_trip() -> None:
    text = "Hello, world!\nTo be or not to be."
    tok = CharTokenizer.from_text(text)
    assert tok.decode(tok.encode(text)) == text


def test_vocab_sorted_unique() -> None:
    tok = CharTokenizer.from_text("cbaaba")
    assert tok.chars == ["a", "b", "c"]
    assert tok.vocab_size == 3


def test_unknown_char_raises() -> None:
    tok = CharTokenizer.from_text("abc")
    with pytest.raises(ValueError, match="unknown character"):
        tok.encode("d")


def test_save_load(tmp_path: Path) -> None:
    text = "abc XYZ\n"
    tok = CharTokenizer.from_text(text)
    path = tmp_path / "tokenizer.json"
    tok.save(path)
    loaded = CharTokenizer.load(path)
    assert loaded.chars == tok.chars
    assert loaded.encode(text) == tok.encode(text)
    assert loaded.decode(tok.encode(text)) == text
