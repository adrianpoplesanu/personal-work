# learn-pytorch

Sandbox for exploring **PyTorch** syntax and semantics while building models (`torch`, `torch.nn`, `math`).

## PyCharm setup

1. **Open** this folder: `File → Open` → select `learn-pytorch`.
2. **Interpreter**: `Settings → Project → Python Interpreter → Add Interpreter → Existing`  
   choose: `.venv/bin/python`
3. If the venv is missing, create it in the terminal:

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

4. Run any file under `playground/` with the green play button, or right‑click → **Run**.

## Layout

```
learn-pytorch/
├── requirements.txt
├── playground/
│   ├── 01_tensors.py      # tensors, broadcasting, autograd
│   ├── 02_nn_modules.py   # nn.Module, layers, losses
│   ├── 03_math_ops.py     # math vs torch math, attention scale, PE
│   └── 04_train_loop.py   # tiny end-to-end train loop
└── scratch/               # drop your own experiments here
```

## Quick run (terminal)

```bash
source .venv/bin/activate
python playground/01_tensors.py
python playground/02_nn_modules.py
python playground/03_math_ops.py
python playground/04_train_loop.py
```
