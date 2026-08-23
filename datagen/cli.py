import argparse

from .game import GameRunner

def main () -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--count", type=int)
    args = parser.parse_args()

    game_count = args.count

    with GameRunner(1) as game_runner:
        for i in range(game_count):
            game_runner.generate_game()

    return 0
