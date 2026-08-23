from pathlib import Path

import chess.engine

ENGINE_PATH: Path = Path("./surveyor")
NODES: int = 5000
VERIFICATION_SEARCH_NODES = 50000
VERIFICATION_BOUND = chess.engine.Cp(150)
HASH = 1
PRINT_FREQUENCY = 100
