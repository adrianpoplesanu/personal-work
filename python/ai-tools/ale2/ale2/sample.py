"""Generate text from a saved ale2 checkpoint."""

import argparse

from ale2.ale2config import Ale2Config
from ale2.train import generate_gpt, load_gpt


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--checkpoint", default=Ale2Config.checkpoint_path)
    parser.add_argument("--prompt", default="a")
    parser.add_argument("--max-new-tokens", type=int, default=20)
    parser.add_argument("--temperature", type=float, default=1.0)
    parser.add_argument("--top-k", type=int, default=1)
    args = parser.parse_args()
    tokenizer, params = load_gpt(args.checkpoint)
    print(
        generate_gpt(
            tokenizer,
            params,
            args.prompt,
            args.max_new_tokens,
            temperature=args.temperature,
            top_k=args.top_k,
        )
    )


if __name__ == "__main__":
    main()
