"""Tests for BpeTokenizer."""

from __future__ import annotations

from pathlib import Path

import pytest

from ale1.tokenizer import BpeTokenizer


def test_round_trip() -> None:
    text = "Hello, world!\nTo be or not to be."
    tok = BpeTokenizer.train(text, vocab_size=300)
    assert tok.decode(tok.encode(text)) == text


def test_vocab_grows_with_merges() -> None:
    text = "low low low low lower lower newest newest newest"
    tok = BpeTokenizer.train(text, vocab_size=280)
    assert tok.vocab_size >= 256
    assert tok.vocab_size <= 280
    assert len(tok.merges) == tok.vocab_size - 256


def test_encode_produces_fewer_tokens_than_bytes() -> None:
    text = "the the the the the the the the"
    tok = BpeTokenizer.train(text, vocab_size=270)
    ids = tok.encode(text)
    assert len(ids) < len(text.encode("utf-8"))


def test_save_load(tmp_path: Path) -> None:
    text = "abc XYZ\nhello hello hello"
    tok = BpeTokenizer.train(text, vocab_size=280)
    path = tmp_path / "tokenizer.json"
    tok.save(path)
    loaded = BpeTokenizer.load(path)
    assert loaded.vocab_size == tok.vocab_size
    assert loaded.encode(text) == tok.encode(text)
    assert loaded.decode(tok.encode(text)) == text


def test_load_rejects_old_char_tokenizer(tmp_path: Path) -> None:
    path = tmp_path / "tokenizer.json"
    path.write_text('{"chars": ["a", "b", "c"]}', encoding="utf-8")
    with pytest.raises(ValueError, match="character tokenizer"):
        BpeTokenizer.load(path)


def test_unknown_token_id_raises() -> None:
    tok = BpeTokenizer.train("abc", vocab_size=256)
    with pytest.raises(ValueError, match="unknown token id"):
        tok.decode([99999])
