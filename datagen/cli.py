import argparse
import os
from datetime import datetime
from pathlib import Path

from .game import GameRunner
from .config import PRINT_FREQUENCY
from .data_generation import begin_data_generation

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--count", type=int, required=True)
    parser.add_argument("-o", "--out", type=Path)
    parser.add_argument("-j", "--jobs", type=int, default=os.cpu_count())
    args = parser.parse_args()

    if args.out is not None:
        fout = args.out
    else:
        timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        fout = Path.home() / ".surveyor-data" / f"data-{timestamp}.surveyor-data"

    fout.parent.mkdir(parents=True, exist_ok=True)

    n_workers = max(1, min(args.jobs, args.count))

    begin_data_generation(args.count, n_workers, fout)

    return 0
    