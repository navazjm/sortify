#!/bin/bash

## Copyright (c) 2025 Michael Navarro 
## MIT license, see LICENSE for more details.

set -e
rm -rf build/debug
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
make -C build/debug
# Needed for neovim clangd lsp
[ -L compile_commands.json ] && rm compile_commands.json
ln -s build/debug/compile_commands.json compile_commands.json
