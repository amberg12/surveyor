import argparse
from datetime import datetime
from pathlib import Path
import shutil

from .game import GameRunner

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--count", type=int, required=True)
    parser.add_argument("-o", "--out", type=Path)

    args = parser.parse_args()

    if args.out is not None:
        fout = args.out
    else:
        timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        fout = Path.home() / ".surveyor-data" / f"data-{timestamp}.surveyor-data"

    fout.parent.mkdir(parents=True, exist_ok=True)

    temp = fout.with_suffix(f".1.surveyor-data")

    with temp.open("w") as output:
        with GameRunner(output) as game_runner:
            for _ in range(args.count):
                game_runner.generate_game()

    with fout.open("ab") as output:
        with temp.open("rb") as input:
            shutil.copyfileobj(input, output)

    temp.unlink()

    return 0
