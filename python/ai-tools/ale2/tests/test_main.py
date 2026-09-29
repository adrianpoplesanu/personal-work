from pathlib import Path

from ale2 import __version__
from ale2.ale2config import Ale2Config
from ale2.main import main
from ale2.tokenizer import CharTokenizer


def test_version() -> None:
    assert __version__ == "0.1.0"


def test_main_saves_tokenizer() -> None:
    main()
    path = Path(Ale2Config().checkpoint_path) / "tokenizer.json"
    assert path.exists()
    tok = CharTokenizer.load(path)
    assert tok.decode(tok.encode("ale2 is ready")) == "ale2 is ready"
