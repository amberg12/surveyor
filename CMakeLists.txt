cmake_minimum_required(VERSION 4.2)
project(surveyor)

set(CMAKE_CXX_STANDARD 23)

add_executable(surveyor
        surveyor/main.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(surveyor PRIVATE -mavx2 -mbmi2)
endif ()
