# Minimal character-level LLM (ale1)

A tiny decoder-only Transformer in PyTorch that learns next-character prediction on a small text corpus, then generates text by sampling from predicted probabilities.

## Pipeline

1. **Tokenization** — each character maps to an integer id  
2. **Embeddings** — token + position embeddings  
3. **Transformer** — causal self-attention blocks  
4. **Probabilities** — softmax over vocabulary logits (with temperature)  
5. **Sampling** — multinomial / top-k next-character selection  

## Requirements

- Python **3.10–3.12** recommended (PyTorch may not yet ship wheels for every newest Python; prefer 3.11 or 3.12 in PyCharm if 3.14 fails to install `torch`)
- macOS / Linux / Windows

## Open in PyCharm

1. **File → Open** and select this folder (`ale1`).
2. Create a virtual environment:
   - **Settings → Project → Python Interpreter → Add Interpreter → Add Local Interpreter**
   - Choose **Virtualenv**, base interpreter 3.11 or 3.12 if available, location `.venv`
3. Install dependencies in the PyCharm terminal (project root):

```bash
pip install -r requirements.txt
# or editable install:
pip install -e ".[dev]"
```

4. Mark the project root as sources root if needed: right-click project root → **Mark Directory as → Sources Root** (so `import ale1` works).

### Run configurations

**Train**

- Script path: `ale1/train.py`
- Working directory: project root (`.../ale1`)
- Parameters (optional): `--max-steps 500 --device auto`

**Sample**

- Script path: `ale1/sample.py`
- Working directory: project root
- Parameters (optional): `--prompt "To be" --max-new-tokens 200 --temperature 0.8 --top-k 40`

**Tests**

- Use the pytest run configuration, or in the terminal:

```bash
pytest -q
```

## Quick start (terminal)

```bash
python -m ale1.train --max-steps 500 --device auto
python -m ale1.sample --prompt "First Citizen:" --max-new-tokens 200
```

Optional: replace `data/tiny.txt` with the full Tiny Shakespeare corpus:

```bash
python scripts/prepare_data.py
```

## Project layout

```
ale1/
  ale1/
    config.py      # hyperparameters
    tokenizer.py   # character-level encode/decode
    model.py       # embeddings + transformer + generate
    train.py       # training loop + checkpoints
    sample.py      # load checkpoint and sample text
  data/tiny.txt
  scripts/prepare_data.py
  tests/
  checkpoints/     # created after training (gitignored)
```

## Checkpoints

After training, `checkpoints/` contains:

- `tokenizer.json` — character vocabulary  
- `model.pt` — weights + config  

These are required by `sample.py`.
