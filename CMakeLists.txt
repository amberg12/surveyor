cmake_minimum_required(VERSION 3.31.6)
project(uci)

option(BUILD_TOOLS "Build extra tooling binaries" OFF)

set(CMAKE_CXX_STANDARD 23)

add_library(surveyorcore
        lib/util/bit.h
        lib/util/bit_iterator.h
        lib/util/cast_iterator.h
        lib/util/constant.h
        lib/util/integer.h
        lib/util/math.h
        lib/util/multi_array.h
        lib/util/parse.h
        lib/util/static_vector.h
        lib/util/tokenizer.cpp
        lib/util/tokenizer.h
        lib/bitboard.h
        lib/engine.cpp
        lib/engine.h
        lib/engine_output.h
        lib/evaluate.h
        lib/game.cpp
        lib/game.h
        lib/geometry.h
        lib/history.h
        lib/move.cpp
        lib/move.h
        lib/move_generation.cpp
        lib/move_generation.h
        lib/move_picker.h
        lib/node_type.h
        lib/perft.cpp
        lib/perft.h
        lib/piece.h
        lib/position.cpp
        lib/position.h
        lib/repetition_table.h
        lib/score.h
        lib/search.cpp
        lib/search.h
        lib/search_ctrls.h
        lib/see.h
        lib/square.h
        lib/transposition_table.cpp
        lib/transposition_table.h
        lib/zobrist.h
)

target_include_directories(surveyorcore
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
)

add_executable(surveyor
        uci/bench_output.h
        uci/interface.cpp
        uci/interface.h
        uci/main.cpp
        uci/uci_output.h
)

target_link_libraries(surveyor
        PRIVATE surveyorcore
)

if (BUILD_TOOLS)
    add_executable(tuner
            tuner/util/common.h
            tuner/util/filesystem.cpp
            tuner/util/filesystem.h
            tuner/data.cpp
            tuner/data.h
            tuner/main.cpp
    )

    target_link_libraries(tuner
            PRIVATE surveyorcore
    )
endif ()
