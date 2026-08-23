import argparse

from .game import GameRunner

def main () -> int:
    game_runner = GameRunner(1)

    game_runner.generate_game()

    return 0
