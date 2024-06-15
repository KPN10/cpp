#!/bin/bash

compiler_path="/home/developer/toolchain"

cd /home/developer/workspace

if [ ! -d "build_x86_64" ]; then
    mkdir build_x86_64
fi

cd build_x86_64
cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_COMPILER="/usr/bin/g++" \
    ../
cmake --build . -- -j4