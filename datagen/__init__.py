__version__ = "0.1.0"

from .cli import main
from .config import HASH, VERIFICATION_SEARCH_NODES, PRINT_FREQUENCY
from .data_generation import begin_data_generation
from .game import GameRunner
