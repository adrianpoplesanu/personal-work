from ale2 import __version__
from ale2.main import main


def test_version() -> None:
    assert __version__ == "0.1.0"


def test_main_runs(capsys) -> None:
    main()
    assert "ale2 is ready" in capsys.readouterr().out
