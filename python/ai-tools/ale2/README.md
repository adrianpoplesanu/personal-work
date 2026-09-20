# ale2

Python project scaffold ready for PyCharm.

## Requirements

- Python **3.10–3.12** recommended (3.12 is preferred if available)

## Open in PyCharm

1. **File → Open** and select this folder (`ale2`).
2. Create / select the virtual environment:
   - **Settings → Project → Python Interpreter → Add Interpreter → Add Local Interpreter**
   - Choose **Virtualenv**, base interpreter **3.12**, location `.venv`
   - Or point at the existing `.venv` in this folder if already created.
3. Install dependencies in the PyCharm terminal (project root):

```bash
pip install -r requirements.txt
# or editable install:
pip install -e ".[dev]"
```

4. Mark the project root as sources root if needed: right-click project root → **Mark Directory as → Sources Root** (so `import ale2` works).

### Run configurations

**Main**

- Script path: `ale2/main.py`
- Working directory: project root (`.../ale2`)

**Tests**

- Use the pytest run configuration, or in the terminal:

```bash
pytest -q
```

## Quick start (terminal)

```bash
python -m venv .venv
source .venv/bin/activate
pip install -e ".[dev]"
python -m ale2.main
pytest -q
```

## Project layout

```
ale2/
  ale2/
    __init__.py
    main.py
  tests/
  pyproject.toml
  requirements.txt
```
