#!/bin/bash

compiler_path="/home/developer/toolchain"

cd /home/developer/workspace

if [ ! -d "build_aarch64" ]; then
    mkdir build_aarch64
fi

aarch64_compiler_cxx="\
/home/developer/toolchain/\
arm-gnu-toolchain-12.3.rel1-x86_64-aarch64-none-linux-gnu/bin/\
aarch64-none-linux-gnu-g++\
"

cd build_aarch64
cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_COMPILER="${aarch64_compiler_cxx}" \
    ../
cmake --build . -- -j4
