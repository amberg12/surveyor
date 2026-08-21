default: native

ifeq ($(OS), Windows_NT)
    override DETECTED_OS := Windows
    TOOLCHAIN_FILE := -DCMAKE_TOOLCHAIN_FILE=scripts/mingw.cmake
    EXE ?= surveyor.exe
else
    override DETECTED_OS := $(shell uname -s)
    EXE ?= surveyor
    TOOLCHAIN_FILE :=
endif

native:
	cmake -S . -B build/native \
    		-DCMAKE_BUILD_TYPE=Release \
    		-DCMAKE_CXX_FLAGS="-march=native" \
    		$(TOOLCHAIN_FILE)
	cmake --build build/native
	cp build/native/surveyor ./$(EXE)

avx2-bmi2:
	cmake -S . -B build/avx2-bmi2 \
    		-DCMAKE_BUILD_TYPE=Release \
    		-DCMAKE_CXX_FLAGS="-mavx2 -mbmi2" \
    		$(TOOLCHAIN_FILE)
	cmake --build build/avx2-bmi2
	cp build/avx2-bmi2/surveyor ./$(EXE)

x86-64:
	cmake -S . -B build/x86-64 \
    		-DCMAKE_BUILD_TYPE=Release \
    		-DCMAKE_CXX_FLAGS="-march=x86-64" \
    		$(TOOLCHAIN_FILE)
	cmake --build build/x86-64
	cp build/x86-64/surveyor ./$(EXE)

.PHONY: default native avx2-bmi2 x86-64.cmake