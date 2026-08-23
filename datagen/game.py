from dataclasses import dataclass
import random
from typing import TextIO

import chess
import chess.engine

from .config import NODES, HASH, VERIFICATION_SEARCH_NODES, VERIFICATION_BOUND

@dataclass(frozen=True)
class _Move:
    move: str
    score: int
    is_mate: bool = False

    def stringify(self) -> str:
        if self.is_mate:
            return f"{self.move} m{self.score}"
        else:
            return f"{self.move} {self.score}"

class _Game:
    def __init__(self, fen: str):
        self._fen = fen
        self._moves = []
        self._winner = None

    def push_move(self, move: str, score: int, is_mate: bool = False) -> None:
        self._moves.append(_Move(move, score))

    def set_outcome(self, winner: chess.Color | None):
        self._winner = winner

    def stringify(self) -> str:
        return f"{self._winner_string()} {self._fen} {' '.join(move.stringify() for move in self._moves)}"

    def _winner_string(self) -> str:
        if self._winner == chess.WHITE:
            return "1.0"

        if self._winner == chess.BLACK:
            return "0.0"

        return "0.5"

class GameRunner:
    def __init__(self, output: TextIO):
        self._writer = output
        self._engine = chess.engine.SimpleEngine.popen_uci("./surveyor")

        self._engine.configure({
            "Hash": HASH,
            "SoftNodes": True,
        })

    def generate_game(self):
        try:
            board = self._generate_board()
            game = _Game(board.fen())

            while not board.is_game_over(claim_draw=True):
                result = self._engine.play(
                    board,
                    chess.engine.Limit(nodes=NODES),
                    info=chess.engine.INFO_SCORE,
                )

                move = result.move
                score = result.info["score"].relative

                if score.is_mate():
                    game.push_move(move.uci(), score.mate(), True)
                else:
                    game.push_move(move.uci(), score.score())

                board.push(move)

            outcome = board.outcome()

            if outcome is not None:
                game.set_outcome(outcome.winner)

            print(game.stringify(), file=self._writer)
        except chess.InvalidMoveError:
            self.generate_game()
        

    def _generate_board(self) -> chess.Board:
        while True:
            board = chess.Board()

            for _ in range(random.randint(5, 8)):
                move_list = list(board.legal_moves)

                if not len(move_list):
                    return self._generate_board()

                board.push(random.choice(move_list))

            if board.is_game_over():
                return self._generate_board()

            info = self._engine.analyse(
                board,
                chess.engine.Limit(nodes=VERIFICATION_SEARCH_NODES),
            )

            score = info["score"]

            if -VERIFICATION_BOUND < score.relative < VERIFICATION_BOUND:
                return board
            
    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self._engine.quit()
            