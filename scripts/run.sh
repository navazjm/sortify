#!/bin/bash

## Copyright (c) 2025 Michael Navarro 
## MIT license, see LICENSE for more details.

EXECUTABLE=./build/debug/sortify_d

# Parse args
DO_BUILD=false
DO_PURGE_CFG=false

# Iterate over all input arguments
for arg in "$@"; do
    case "$arg" in
        --build)
            DO_BUILD=true
            ;;
        --purge-cfg)
            DO_PURGE_CFG=true
            ;;
        *)
            # Ignore unknown args from being passed to the executable
            ;;
    esac
done

if [ "$DO_PURGE_CFG" = true ]; then
    echo "Purging $HOME/.config/sortify"
    rm -rf "$HOME/.config/sortify"
fi

if [ "$DO_BUILD" = true ]; then
    if ! ./scripts/build.sh; then
        echo "Debug - Build failed!"
        exit 1
    fi
    echo "Debug - Build succeeded!"
fi

# Run the executable if it exists
if [ -f "$EXECUTABLE" ]; then
    "$EXECUTABLE"
else
    echo "Executable not found at $EXECUTABLE. Try running with --build to compile it first."
    exit 1
fi

