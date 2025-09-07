#!/usr/bin/env bash
set -e  # Exit immediately if a command fails

# Names
BUILD_DIR="build"
MAIN_EXEC="main"
OUTPUT_DIR="."

# 1. Create and enter build directory
if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

# 2. Run CMake with Release build type
cmake -S .. -B . -DCMAKE_BUILD_TYPE=Release

# 3. Compile
make -j$(nproc)

# 4. Run tests if they exist
for test_exec in tests_2d tests_3d; do
    if [ -f "$test_exec" ]; then
        echo "Running $test_exec..."
        ./"$test_exec"
    fi
done

# 5. Copy main out and clean everything else
if [ -f "$MAIN_EXEC" ]; then
    cp "$MAIN_EXEC" .. 
fi

cd ..
rm -rf "$BUILD_DIR"

