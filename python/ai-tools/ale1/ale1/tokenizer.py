"""Character-level tokenizer: map each unique character to an integer id."""

from __future__ import annotations

import json
from pathlib import Path


class CharTokenizer:
    """Simple character vocabulary with encode/decode and JSON persistence."""

    def __init__(self, chars: list[str]) -> None:
        if not chars:
            raise ValueError("chars must be a non-empty list")
        if len(chars) != len(set(chars)):
            raise ValueError("chars must be unique")
        self.chars = list(chars)
        self.stoi = {ch: i for i, ch in enumerate(self.chars)}
        self.itos = {i: ch for i, ch in enumerate(self.chars)}

    @classmethod
    def from_text(cls, text: str) -> CharTokenizer:
        chars = sorted(set(text))
        return cls(chars)

    @property
    def vocab_size(self) -> int:
        return len(self.chars)

    def encode(self, text: str) -> list[int]:
        try:
            return [self.stoi[ch] for ch in text]
        except KeyError as exc:
            raise ValueError(f"unknown character not in vocabulary: {exc.args[0]!r}") from exc

    def decode(self, ids: list[int]) -> str:
        try:
            return "".join(self.itos[i] for i in ids)
        except KeyError as exc:
            raise ValueError(f"unknown token id: {exc.args[0]!r}") from exc

    def save(self, path: str | Path) -> None:
        path = Path(path)
        path.parent.mkdir(parents=True, exist_ok=True)
        payload = {"chars": self.chars}
        path.write_text(json.dumps(payload, ensure_ascii=False, indent=2), encoding="utf-8")

    @classmethod
    def load(cls, path: str | Path) -> CharTokenizer:
        payload = json.loads(Path(path).read_text(encoding="utf-8"))
        return cls(payload["chars"])
