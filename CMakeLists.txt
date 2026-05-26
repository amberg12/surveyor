cmake_minimum_required(VERSION 4.2)
project(surveyor)

set(CMAKE_CXX_STANDARD 23)

add_executable(surveyor src/main.cpp
        src/uci.cpp
        src/uci.hpp
        src/square.hpp
        src/util/integer.hpp
        src/util/assert.hpp
        src/util/macro.hpp)
