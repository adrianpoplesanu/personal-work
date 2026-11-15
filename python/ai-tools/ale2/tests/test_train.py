import random
from pathlib import Path

from ale2.ale2config import Ale2Config
from ale2.tokenizer import CharTokenizer
from ale2.train import (
    fit_gpt,
    fit_next_char,
    generate,
    generate_gpt,
    get_batch,
    load_gpt,
    save_gpt,
    next_char_pairs,
    train,
    train_next_char,
)

_TINY = dict(block_size=4, batch_size=4)


def test_next_char_pairs() -> None:
    ids = CharTokenizer.from_text("ab").encode("abab")
    assert next_char_pairs(ids) == ([0, 1, 0], [1, 0, 1])


def test_next_char_loss_falls() -> None:
    first, last = train_next_char("ababababab", steps=50, lr=0.5, n_embd=4)
    assert last < first


def test_top_k_one_continues_abab() -> None:
    tokenizer, table, w, b, _, _ = fit_next_char("ababababab", steps=50, lr=0.5, n_embd=4)
    assert generate(tokenizer, table, w, b, "a", 1, top_k=1) == "ab"
    assert generate(tokenizer, table, w, b, "b", 1, top_k=1) == "ba"


def test_get_batch_windows_have_fixed_length() -> None:
    ids = list(range(20))
    batch = get_batch(ids, batch_size=3, block_size=4, rng=random.Random(0))
    assert len(batch) == 3
    for inputs, targets in batch:
        assert len(inputs) == 4
        assert len(targets) == 4
        assert targets[:-1] == inputs[1:]


def test_gpt_window_loss_falls() -> None:
    _, _, first, last = fit_gpt("ababababab", steps=30, lr=0.5, n_embd=4, **_TINY)
    assert last < first


def test_two_layers_loss_falls() -> None:
    _, params, first, last = fit_gpt("ababababab", steps=20, lr=0.5, n_embd=4, n_layer=2, **_TINY)
    assert len(params["blocks"]) == 2
    assert len(params["pos_table"]) == 4
    assert last < first


def test_gpt_top_k_one_continues_abab() -> None:
    tokenizer, params, _, _ = fit_gpt("ababababab", steps=40, lr=0.5, n_embd=4, **_TINY)
    assert generate_gpt(tokenizer, params, "a", 1, top_k=1) == "ab"
    assert generate_gpt(tokenizer, params, "b", 1, top_k=1) == "ba"


def test_generate_continues_past_block_size() -> None:
    tokenizer, params, _, _ = fit_gpt("ababababab", steps=5, lr=0.5, n_embd=4, **_TINY)
    text = generate_gpt(tokenizer, params, "ababababab", 3, top_k=1)
    assert text.startswith("ababababab")
    assert len(text) == 13


def test_checkpoint_round_trip_generates(tmp_path: Path) -> None:
    tokenizer, params, _, _ = fit_gpt("ababababab", steps=40, lr=0.5, n_embd=4, **_TINY)
    save_gpt(tokenizer, params, tmp_path)
    loaded_tokenizer, loaded_params = load_gpt(tmp_path)
    assert generate_gpt(loaded_tokenizer, loaded_params, "a", 1, top_k=1) == "ab"
    assert generate_gpt(loaded_tokenizer, loaded_params, "b", 1, top_k=1) == "ba"


def test_train_reads_file_text(tmp_path: Path, capsys) -> None:
    path = tmp_path / "source.txt"
    checkpoint = tmp_path / "checkpoints"
    path.write_text("ababababab", encoding="utf-8")
    config = Ale2Config(
        data_path=str(path),
        checkpoint_path=str(checkpoint),
        max_steps=20,
        learning_rate=0.5,
        n_embd=4,
        block_size=4,
        batch_size=4,
    )
    train(config)
    captured = capsys.readouterr()
    first, last = (float(part) for part in captured.out.removeprefix("loss ").split(" -> "))
    assert last < first
    assert (checkpoint / "tokenizer.json").exists()
    assert (checkpoint / "model.json").exists()
