cmake_minimum_required(VERSION 4.2)
project(surveyor)

set(CMAKE_CXX_STANDARD 23)

set(SRCS
        src/uci.cpp
        src/uci.hpp
        src/square.hpp
        src/util/integer.hpp
        src/piece.hpp
        src/util/constant.hpp
        src/util/bit_iterator.hpp
        src/util/bit.hpp
        src/util/cast_iterator.hpp
        src/position.cpp
        src/position.hpp
        src/util/parse.hpp
        src/util/static_vector.hpp
        src/move_generation.cpp
        src/move_generation.hpp
        src/move.cpp
        src/move.hpp
        src/geometry.hpp
        src/bitboard.hpp
        src/evaluate.hpp
        src/score.hpp
        src/search_controls.hpp
        src/search.cpp
        src/search.hpp
        src/evaluation_constants.hpp
        src/move_picker.hpp
        src/zobrist.hpp
        src/util/multi_array.hpp
        src/transposition_table.cpp
        src/transposition_table.hpp)

add_executable(surveyor src/main.cpp
        ${SRCS}
        src/node_type.hpp)

add_executable(surveyor_tuner src/evaluation_tuner/evaluation_tuner_main.cpp
        ${SRCS})
