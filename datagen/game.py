from dataclasses import dataclass
import random

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

    def push_move(self, move: str, score: int, is_mate: bool = False) -> None:
        self._moves.append(_Move(move, score))

    def stringify(self) -> str:
        return f"{self._fen} {' '.join(move.stringify() for move in self._moves)}"

class GameRunner:
    def __init__(self, id: int):
        self._id = id
        self._engine = chess.engine.SimpleEngine.popen_uci("./surveyor")

        self._engine.configure({
            "Hash": HASH,
            "SoftNodes": True,
        })

    def generate_game(self):
        board = self._generate_board()
        game = _Game(board.fen())

        while not board.is_game_over():
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

        print(game.stringify())
        

    def _generate_board(self) -> chess.Board:
        while True:
            board = chess.Board()

            for _ in range(random.randint(5, 8)):
                board.push(random.choice(list(board.legal_moves)))

            info = self._engine.analyse(
                board,
                chess.engine.Limit(nodes=VERIFICATION_SEARCH_NODES),
            )

            score = info["score"]

            if -VERIFICATION_BOUND < score.relative < VERIFICATION_BOUND:
                return board
            