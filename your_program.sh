#!/bin/sh
set -e

# Ensure cmake is found
export PATH="/opt/homebrew/bin:$PATH"

# Compile using CMake WITHOUT vcpkg
(
  cd "$(dirname "$0")"
  cmake -B build -S .
  cmake --build build
)

# Run the compiled binary
exec ./build/bittorrent "$@"
