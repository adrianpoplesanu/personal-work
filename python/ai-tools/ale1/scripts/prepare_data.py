#!/usr/bin/env python3
"""Download Karpathy's Tiny Shakespeare into data/tiny.txt if desired."""

from __future__ import annotations

import argparse
import urllib.request
from pathlib import Path

URL = (
    "https://raw.githubusercontent.com/karpathy/char-rnn/master/data/"
    "tinyshakespeare/input.txt"
)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--out",
        type=Path,
        default=Path("data/tiny.txt"),
        help="Destination path for the corpus",
    )
    args = parser.parse_args()
    args.out.parent.mkdir(parents=True, exist_ok=True)
    print(f"Downloading {URL}")
    urllib.request.urlretrieve(URL, args.out)
    text = args.out.read_text(encoding="utf-8")
    print(f"Wrote {len(text):,} characters to {args.out}")


if __name__ == "__main__":
    main()
