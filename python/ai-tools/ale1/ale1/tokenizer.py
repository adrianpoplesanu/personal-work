"""Byte-level BPE tokenizer (GPT-2 style, trained on the corpus)."""

from __future__ import annotations

import json
from collections import Counter
from pathlib import Path


def _get_pair_counts(ids: list[int]) -> Counter[tuple[int, int]]:
    counts: Counter[tuple[int, int]] = Counter()
    for a, b in zip(ids, ids[1:]):
        counts[(a, b)] += 1
    return counts


def _merge_pair(ids: list[int], pair: tuple[int, int], new_id: int) -> list[int]:
    a, b = pair
    out: list[int] = []
    i = 0
    while i < len(ids):
        if i < len(ids) - 1 and ids[i] == a and ids[i + 1] == b:
            out.append(new_id)
            i += 2
        else:
            out.append(ids[i])
            i += 1
    return out


class BpeTokenizer:
    """
    Byte-level BPE: base vocab is 256 UTF-8 bytes, then learned merges.

    API mirrors the old CharTokenizer: encode / decode / save / load / vocab_size.
    """

    def __init__(
        self,
        merges: dict[tuple[int, int], int],
        vocab_size: int,
    ) -> None:
        if vocab_size < 256:
            raise ValueError("vocab_size must be at least 256 (byte alphabet)")
        self.merges = dict(merges)
        self._vocab_size = vocab_size
        # id -> raw bytes for decoding
        self.vocab: dict[int, bytes] = {i: bytes([i]) for i in range(256)}
        for (a, b), idx in sorted(self.merges.items(), key=lambda kv: kv[1]):
            self.vocab[idx] = self.vocab[a] + self.vocab[b]

    @classmethod
    def train(cls, text: str, vocab_size: int = 512) -> BpeTokenizer:
        """Learn merges on UTF-8 bytes of ``text`` until ``vocab_size`` is reached."""
        if vocab_size < 256:
            raise ValueError("vocab_size must be at least 256")
        ids = list(text.encode("utf-8"))
        merges: dict[tuple[int, int], int] = {}
        num_merges = vocab_size - 256

        for i in range(num_merges):
            counts = _get_pair_counts(ids)
            if not counts:
                break
            pair = max(counts, key=counts.get)  # type: ignore[arg-type]
            new_id = 256 + i
            ids = _merge_pair(ids, pair, new_id)
            merges[pair] = new_id

        actual_size = 256 + len(merges)
        return cls(merges=merges, vocab_size=actual_size)

    @property
    def vocab_size(self) -> int:
        return self._vocab_size

    def encode(self, text: str) -> list[int]:
        ids = list(text.encode("utf-8"))
        # Apply merges in creation order (lowest new id first)
        for pair, new_id in sorted(self.merges.items(), key=lambda kv: kv[1]):
            ids = _merge_pair(ids, pair, new_id)
        return ids

    def decode(self, ids: list[int]) -> str:
        try:
            raw = b"".join(self.vocab[i] for i in ids)
        except KeyError as exc:
            raise ValueError(f"unknown token id: {exc.args[0]!r}") from exc
        return raw.decode("utf-8", errors="replace")

    def save(self, path: str | Path) -> None:
        path = Path(path)
        path.parent.mkdir(parents=True, exist_ok=True)
        # JSON keys must be strings; store merges as ["a,b", id]
        payload = {
            "type": "bpe",
            "vocab_size": self._vocab_size,
            "merges": [[a, b, idx] for (a, b), idx in sorted(self.merges.items(), key=lambda kv: kv[1])],
        }
        path.write_text(json.dumps(payload, indent=2), encoding="utf-8")

    @classmethod
    def load(cls, path: str | Path) -> BpeTokenizer:
        payload = json.loads(Path(path).read_text(encoding="utf-8"))
        if payload.get("type") == "chars" or "chars" in payload and "merges" not in payload:
            raise ValueError(
                f"{path} looks like an old character tokenizer. "
                "Retrain with `python -m ale1.train` to create a BPE tokenizer.json."
            )
        merges = {(int(a), int(b)): int(idx) for a, b, idx in payload["merges"]}
        return cls(merges=merges, vocab_size=int(payload["vocab_size"]))
