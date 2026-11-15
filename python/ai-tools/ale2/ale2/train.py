import json
import random
from pathlib import Path

from ale2.ale2config import Ale2Config
from ale2.ops import (
    cross_entropy,
    cross_entropy_backward,
    embed,
    embed_backward,
    adamw_step,
    gpt_backward,
    gpt_forward,
    linear,
    linear_backward,
    sample,
    sgd_step,
)
from ale2.tokenizer import CharTokenizer


def next_char_pairs(ids: list[int]) -> tuple[list[int], list[int]]:
    """Input token and the token that follows it."""
    if len(ids) < 2:
        raise ValueError("need at least two tokens")
    return ids[:-1], ids[1:]


def fit_next_char(
    text: str,
    steps: int = 50,
    lr: float = 0.5,
    n_embd: int = 4,
):
    """Train embed + linear. Returns tokenizer, table, w, b, first loss, last loss."""
    tokenizer = CharTokenizer.from_text(text)
    inputs, targets = next_char_pairs(tokenizer.encode(text))
    vocab = tokenizer.vocab_size
    table = [[(i + 1) * (j + 1) / vocab for j in range(n_embd)] for i in range(vocab)]
    w = [[0.0] * vocab for _ in range(n_embd)]
    b = [0.0] * vocab

    def loss_of() -> float:
        return cross_entropy(linear(embed(table, inputs), w, b), targets)

    first = loss_of()
    for _ in range(steps):
        x = embed(table, inputs)
        logits = linear(x, w, b)
        dy = cross_entropy_backward(logits, targets)
        dx, dw, db = linear_backward(x, w, dy)
        dtable = embed_backward(table, inputs, dx)
        sgd_step(w, b, dw, db, lr)
        sgd_step(table, [], dtable, [], lr)
    return tokenizer, table, w, b, first, loss_of()


def train_next_char(
    text: str,
    steps: int = 50,
    lr: float = 0.5,
    n_embd: int = 4,
) -> tuple[float, float]:
    """Fit embed + linear to predict the next character. Returns first and last loss."""
    *_, first, last = fit_next_char(text, steps=steps, lr=lr, n_embd=n_embd)
    return first, last


_BLOCK_KEYS = (
    "ln1_gamma",
    "ln1_beta",
    "w_qkv",
    "b_qkv",
    "w_out",
    "b_out",
    "ln2_gamma",
    "ln2_beta",
    "w1",
    "b1",
    "w2",
    "b2",
)
_MODEL_KEYS = (
    "token_table",
    "pos_table",
    "blocks",
    "ln_f_gamma",
    "ln_f_beta",
    "w_head",
    "b_head",
)


def _zeros(rows: int, cols: int) -> list[list[float]]:
    return [[0.0] * cols for _ in range(rows)]


def _vector(length: int, value: float = 0.0) -> list[float]:
    return [value] * length


def _block_params(n_embd: int) -> dict:
    hidden = 4 * n_embd
    return {
        "ln1_gamma": _vector(n_embd, 1.0),
        "ln1_beta": _vector(n_embd),
        "w_qkv": _zeros(n_embd, 3 * n_embd),
        "b_qkv": _vector(3 * n_embd),
        "w_out": _zeros(n_embd, n_embd),
        "b_out": _vector(n_embd),
        "ln2_gamma": _vector(n_embd, 1.0),
        "ln2_beta": _vector(n_embd),
        "w1": _zeros(n_embd, hidden),
        "b1": _vector(hidden),
        "w2": _zeros(hidden, n_embd),
        "b2": _vector(n_embd),
    }


def init_gpt(vocab: int, n_embd: int, length: int, n_head: int = 1, n_layer: int = 1) -> dict:
    """GPT with n_layer blocks. Token rows start distinct; other weights start at zero."""
    if n_embd % n_head != 0:
        raise ValueError("n_embd must be divisible by n_head")
    return {
        "token_table": [[(i + 1) * (j + 1) / vocab for j in range(n_embd)] for i in range(vocab)],
        "pos_table": _zeros(length, n_embd),
        "blocks": [_block_params(n_embd) for _ in range(n_layer)],
        "ln_f_gamma": _vector(n_embd, 1.0),
        "ln_f_beta": _vector(n_embd),
        "w_head": _zeros(n_embd, vocab),
        "b_head": _vector(vocab),
        "n_head": n_head,
    }


def _n_head(params: dict) -> int:
    return params.get("n_head", 1)


def _model_args(params: dict) -> tuple:
    blocks = [tuple(block[key] for key in _BLOCK_KEYS) for block in params["blocks"]]
    return (
        params["token_table"],
        params["pos_table"],
        blocks,
        params["ln_f_gamma"],
        params["ln_f_beta"],
        params["w_head"],
        params["b_head"],
    )


def _zeros_like(param):
    if param and isinstance(param[0], list):
        return [_zeros_like(row) for row in param]
    return [0.0] * len(param)


def _leaf_state(param):
    return {"m": _zeros_like(param), "v": _zeros_like(param)}


def _init_adamw_state(params: dict) -> dict:
    return {
        "token_table": _leaf_state(params["token_table"]),
        "pos_table": _leaf_state(params["pos_table"]),
        "blocks": [
            {key: _leaf_state(block[key]) for key in _BLOCK_KEYS}
            for block in params["blocks"]
        ],
        "ln_f_gamma": _leaf_state(params["ln_f_gamma"]),
        "ln_f_beta": _leaf_state(params["ln_f_beta"]),
        "w_head": _leaf_state(params["w_head"]),
        "b_head": _leaf_state(params["b_head"]),
    }


def _apply_adamw(param, grad, state, lr: float, step: int, weight_decay: float) -> None:
    adamw_step(param, grad, state["m"], state["v"], lr, step, wd=weight_decay)


def _apply_gpt_grads(params: dict, grads: tuple, state: dict, lr: float, step: int, weight_decay: float) -> None:
    d_token, d_pos, block_grads, dln_f_gamma, dln_f_beta, dw_head, db_head = grads
    _apply_adamw(params["token_table"], d_token, state["token_table"], lr, step, weight_decay)
    _apply_adamw(params["pos_table"], d_pos, state["pos_table"], lr, step, weight_decay)
    for block, block_grad, block_state in zip(params["blocks"], block_grads, state["blocks"]):
        for key, grad in zip(_BLOCK_KEYS, block_grad):
            _apply_adamw(block[key], grad, block_state[key], lr, step, weight_decay)
    _apply_adamw(params["ln_f_gamma"], dln_f_gamma, state["ln_f_gamma"], lr, step, weight_decay)
    _apply_adamw(params["ln_f_beta"], dln_f_beta, state["ln_f_beta"], lr, step, weight_decay)
    _apply_adamw(params["w_head"], dw_head, state["w_head"], lr, step, weight_decay)
    _apply_adamw(params["b_head"], db_head, state["b_head"], lr, step, weight_decay)


def get_batch(ids: list[int], batch_size: int, block_size: int, rng: random.Random):
    """Random windows of block_size tokens and the token that follows each one."""
    max_start = len(ids) - block_size - 1
    if max_start < 0:
        raise ValueError(f"corpus too short ({len(ids)} tokens) for block_size={block_size}")
    windows = []
    for _ in range(batch_size):
        start = rng.randrange(max_start + 1)
        windows.append((ids[start:start + block_size], ids[start + 1:start + block_size + 1]))
    return windows


def gpt_window_loss(inputs: list[int], targets: list[int], params: dict) -> float:
    """Cross-entropy of next-token logits for one context window."""
    logits = gpt_forward(inputs, *_model_args(params), n_head=_n_head(params))
    return cross_entropy(logits, targets)


def _window_grads(inputs, targets, params):
    n_head = _n_head(params)
    logits = gpt_forward(inputs, *_model_args(params), n_head=n_head)
    loss = cross_entropy(logits, targets)
    dy = cross_entropy_backward(logits, targets)
    return loss, gpt_backward(inputs, *_model_args(params), dy, n_head)


def _zero_tree(grad):
    if isinstance(grad, (list, tuple)) and grad and isinstance(grad[0], (list, tuple)):
        return [_zero_tree(item) for item in grad]
    return [0.0] * len(grad)


def _add_tree(total, grad) -> None:
    if isinstance(grad, (list, tuple)) and grad and isinstance(grad[0], (list, tuple)):
        for row, grow in zip(total, grad):
            _add_tree(row, grow)
        return
    for j, value in enumerate(grad):
        total[j] += value


def _scale_tree(total, scale: float) -> None:
    if total and isinstance(total[0], list):
        for row in total:
            _scale_tree(row, scale)
        return
    for j, value in enumerate(total):
        total[j] = value * scale


def gpt_batch_step(batch, params, state, lr, step, weight_decay) -> float:
    """One AdamW step on the mean gradient of a batch. Returns the mean loss."""
    total = None
    loss_sum = 0.0
    for inputs, targets in batch:
        loss, grads = _window_grads(inputs, targets, params)
        loss_sum += loss
        if total is None:
            total = _zero_tree(grads)
        _add_tree(total, grads)
    _scale_tree(total, 1.0 / len(batch))
    _apply_gpt_grads(params, total, state, lr, step, weight_decay)
    return loss_sum / len(batch)


def fit_gpt(
    text: str,
    steps: int = 50,
    lr: float = 0.5,
    n_embd: int = 4,
    n_head: int = 1,
    n_layer: int = 1,
    weight_decay: float = 0.01,
    block_size: int = 64,
    batch_size: int = 32,
    seed: int = 42,
):
    """Train on random block_size windows. Returns tokenizer, params, first loss, last loss."""
    tokenizer = CharTokenizer.from_text(text)
    ids = tokenizer.encode(text)
    params = init_gpt(tokenizer.vocab_size, n_embd, block_size, n_head, n_layer)
    state = _init_adamw_state(params)
    rng = random.Random(seed)
    first = None
    last = None
    for step in range(1, steps + 1):
        batch = get_batch(ids, batch_size, block_size, rng)
        last = gpt_batch_step(batch, params, state, lr, step, weight_decay)
        if first is None:
            first = last
    return tokenizer, params, first, last


def save_gpt(tokenizer, params: dict, checkpoint_dir: str | Path) -> None:
    """Write tokenizer.json and model.json under checkpoint_dir."""
    checkpoint_dir = Path(checkpoint_dir)
    checkpoint_dir.mkdir(parents=True, exist_ok=True)
    tokenizer.save(checkpoint_dir / "tokenizer.json")
    payload = {key: params[key] for key in _MODEL_KEYS}
    payload["n_head"] = _n_head(params)
    (checkpoint_dir / "model.json").write_text(json.dumps(payload))


def load_gpt(checkpoint_dir: str | Path):
    """Load a tokenizer and GPT parameters saved by save_gpt."""
    checkpoint_dir = Path(checkpoint_dir)
    tok_path = checkpoint_dir / "tokenizer.json"
    model_path = checkpoint_dir / "model.json"
    if not tok_path.exists() or not model_path.exists():
        raise FileNotFoundError(
            f"missing checkpoint files in {checkpoint_dir} "
            "(expected tokenizer.json and model.json)"
        )
    tokenizer = CharTokenizer.load(tok_path)
    payload = json.loads(model_path.read_text())
    params = {key: payload[key] for key in _MODEL_KEYS}
    params["n_head"] = payload.get("n_head", 1)
    return tokenizer, params


def generate_gpt(tokenizer, params, prompt: str, n: int, temperature=1.0, top_k=None, rng=None) -> str:
    """Append n characters. Each step attends only to the last block_size tokens."""
    ids = tokenizer.encode(prompt)
    block_size = len(params["pos_table"])
    for _ in range(n):
        window = ids[-block_size:]
        logits = gpt_forward(window, *_model_args(params), n_head=_n_head(params))[-1]
        ids.append(sample(logits, temperature=temperature, top_k=top_k, rng=rng))
    return tokenizer.decode(ids)


def generate(tokenizer, table, w, b, prompt: str, n: int, temperature=1.0, top_k=None, rng=None) -> str:
    """Append n sampled characters, each conditioned on the last one."""
    ids = tokenizer.encode(prompt)
    for _ in range(n):
        logits = linear(embed(table, [ids[-1]]), w, b)[0]
        ids.append(sample(logits, temperature=temperature, top_k=top_k, rng=rng))
    return tokenizer.decode(ids)


def train(config: Ale2Config) -> None:
    text = Path(config.data_path).read_text(encoding="utf-8")
    tokenizer, params, first, last = fit_gpt(
        text,
        steps=config.max_steps,
        lr=config.learning_rate,
        n_embd=config.n_embd,
        n_head=config.n_head,
        n_layer=config.n_layer,
        weight_decay=config.weight_decay,
        block_size=config.block_size,
        batch_size=config.batch_size,
        seed=config.seed,
    )
    save_gpt(tokenizer, params, config.checkpoint_path)
    print(f"loss {first:.4f} -> {last:.4f}")


def main():
    print("running train...")
    config = Ale2Config()
    train(config)


if __name__ == "__main__":
    main()
