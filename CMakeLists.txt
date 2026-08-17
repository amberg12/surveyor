cmake_minimum_required(VERSION 4.2)
project(surveyor)

set(CMAKE_CXX_STANDARD 23)

add_library(libsurveyor
        lib/util/tokenizer.h
        lib/util/tokenizer.cpp
        lib/util/integer.h
)

target_include_directories(libsurveyor
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
)

add_executable(surveyor
        surveyor/main.cpp
        surveyor/interface.cpp
        surveyor/interface.h
)

target_link_libraries(surveyor
        PRIVATE libsurveyor
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(surveyor PRIVATE -mavx2 -mbmi2)
    target_compile_options(libsurveyor PRIVATE -mavx2 -mbmi2)
endif ()
