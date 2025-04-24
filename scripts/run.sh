#!/bin/bash

## Copyright (c) 2025 Michael Navarro 
## MIT license, see LICENSE for more details.

EXECUTABLE=./build/debug/sortify_d

if [ "$1" == "--build" ]; then
    if ! ./scripts/build.sh; then
        echo "Debug - Build failed!"
        exit 1
    fi

    echo "Debug - Build succeeded!"
    shift # Remove the --build arg so it doesn't get passed to the executable
fi

if [ -f "$EXECUTABLE" ]; then
    "$EXECUTABLE" "$@"
else
    echo "Executable not found at $EXECUTABLE. Try running with --build to compile it first."
    exit 1
fi
