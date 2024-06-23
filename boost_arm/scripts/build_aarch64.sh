#!/bin/bash

compiler_version=$1
filename=$2
output_filename=$3
compiler_path="/home/developer/toolchain"
compiler="${compiler_path}/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++"
compile_options="-std=c++17 -O3 -Wall -Wpedantic -static -I/opt/boost/include -L/opt/boost/lib -lboost_chrono -lpthread"
echo "compile options: ${compile_options}"
# "-I",
# "/opt/boost/include",
# "-L",
# "/opt/boost/lib/**",

$compiler $filename -o $output_filename $compile_options
