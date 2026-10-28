# Familiar shortcuts around the CMake/Ninja build. Override with: make CC=gcc test
CC = clang
PROGRAM ?= hello
.DEFAULT_GOAL := debug-build

.PHONY: setup debug-build release sanitize test test-sanitize run run-release run-sanitize debug format format-check tidy clean

setup:
	CC=$(CC) cmake --preset debug

debug-build:
	CC=$(CC) cmake --preset debug
	cmake --build build/debug

release:
	CC=$(CC) cmake --preset release
	cmake --build build/release

sanitize:
	CC=$(CC) cmake --preset sanitize
	cmake --build build/sanitize

test: debug-build
	ctest --test-dir build/debug --output-on-failure

test-sanitize: sanitize
	ctest --test-dir build/sanitize --output-on-failure

run: setup
	cmake --build build/debug --target $(PROGRAM)
	./build/debug/$(PROGRAM)

run-release:
	CC=$(CC) cmake --preset release
	cmake --build build/release --target $(PROGRAM)
	./build/release/$(PROGRAM)

run-sanitize:
	CC=$(CC) cmake --preset sanitize
	cmake --build build/sanitize --target $(PROGRAM)
	./build/sanitize/$(PROGRAM)

debug: setup
	cmake --build build/debug --target $(PROGRAM)
	lldb -- ./build/debug/$(PROGRAM)

format:
	find src include tests -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +

format-check:
	find src include tests -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format --dry-run --Werror {} +

tidy: setup
	find src tests -type f -name '*.c' -exec clang-tidy -p build/debug {} +

clean:
	cmake -E rm -rf build
