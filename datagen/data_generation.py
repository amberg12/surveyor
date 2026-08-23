from concurrent.futures import ProcessPoolExecutor, as_completed
from multiprocessing import Value
from pathlib import Path
import shutil
from typing import TextIO

from .config import PRINT_FREQUENCY
from .game import GameRunner

_counter: Value = None
_target: int = None

def _init_worker(counter: Value, target: int, report_every: int) -> None:
    global _counter, _target
    _counter = counter
    _target = target

def _claim_next() -> int | None:
    """Atomically claim one unit of work. Returns the claimed index (1-based),
    or None when exhausted."""
    with _counter.get_lock():
        if _counter.value >= _target:
            return None
        _counter.value += 1
        return _counter.value

def _generate_chunk(temp_path: Path) -> Path:
    with temp_path.open("w") as output:
        with GameRunner(output) as game_runner:
            while (claimed := _claim_next()) is not None:
                game_runner.generate_game()
                if claimed % PRINT_FREQUENCY == 0 or claimed == _target:
                    print(f"{claimed}/{_target}", flush=True)
    return temp_path

def begin_data_generation(game_count: int, n_workers: int, fout: TextIO):
    temp_paths = [fout.with_suffix(f".{i}.surveyor-data") for i in range(n_workers)]

    counter = Value("i", 0)

    with ProcessPoolExecutor(
        max_workers=n_workers,
        initializer=_init_worker,
        initargs=(counter, game_count, PRINT_FREQUENCY),
    ) as executor:
        futures = [executor.submit(_generate_chunk, temp_path) for temp_path in temp_paths]
        for future in as_completed(futures):
            future.result()

    with fout.open("ab") as output:
        for temp_path in temp_paths:
            with temp_path.open("rb") as input_:
                shutil.copyfileobj(input_, output)
            temp_path.unlink()