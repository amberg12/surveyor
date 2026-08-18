cmake_minimum_required(VERSION 4.2)
project(surveyor)

set(CMAKE_CXX_STANDARD 23)

add_library(libsurveyor
        lib/util/bit.h
        lib/util/bit_iterator.h
        lib/util/cast_iterator.h
        lib/util/constant.h
        lib/util/integer.h
        lib/util/multi_array.h
        lib/util/parse.h
        lib/util/static_vector.h
        lib/util/tokenizer.cpp
        lib/util/tokenizer.h
        lib/bitboard.h
        lib/engine.cpp
        lib/engine.h
        lib/engine_output.h
        lib/game.cpp
        lib/game.h
        lib/geometry.h
        lib/move.cpp
        lib/move.h
        lib/move_generation.cpp
        lib/move_generation.h
        lib/perft.cpp
        lib/perft.h
        lib/piece.h
        lib/position.cpp
        lib/position.h
        lib/score.h
        lib/search.cpp
        lib/search.h
        lib/search_limits.h
        lib/square.h
        lib/zobrist.h
)

target_include_directories(libsurveyor
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
)

add_executable(surveyor
        surveyor/interface.cpp
        surveyor/interface.h
        surveyor/main.cpp
        surveyor/uci_output.h
)

target_link_libraries(surveyor
        PRIVATE libsurveyor
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(surveyor PRIVATE -mavx2 -mbmi2)
    target_compile_options(libsurveyor PRIVATE -mavx2 -mbmi2)
endif ()
