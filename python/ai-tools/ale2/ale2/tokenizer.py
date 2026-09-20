from __future__ import annotations

import json
from pathlib import Path

class CharTokenizer:
    def __init__(self, chars: list[str]) -> None:
        self.chars = chars

    def save(self, path: str | Path) -> None:
        path = Path(path)
        path.parent.mkdir(parents=True, exist_ok=True)
        payload = {"chars": self.chars}
        path.write_text(json.dumps(payload))

    @classmethod
    def from_text(cls, text: str) -> CharTokenizer:
        chars = sorted(set(text))
        return cls(chars)

    @classmethod
    def load(cls, path: str) -> CharTokenizer:
        payload = json.loads(Path(path).read_text())
        return cls(payload['chars'])