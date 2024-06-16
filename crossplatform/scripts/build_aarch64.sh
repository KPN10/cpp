#!/bin/bash

compiler_version=$1
compiler_path="/home/developer/toolchain"

cd /home/developer/workspace
build_dir="build_aarch64_gcc_${compiler_version}"
if [ ! -d $build_dir ]; then
    mkdir $build_dir
fi

if [ "${compiler_version}" == "10.3" ]; then
    aarch64_compiler_cxx="${compiler_path}/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++"
elif [ "${compiler_version}" == "11.2" ]; then
    aarch64_compiler_cxx="${compiler_path}/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++"
elif [ "${compiler_version}" == "12.3" ];then
    aarch64_compiler_cxx="${compiler_path}/arm-gnu-toolchain-12.3.rel1-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++"
else
    echo "Compiler version: n/a"
    aarch64_compiler_cxx="n/a"
fi

cd $build_dir
cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_COMPILER="${aarch64_compiler_cxx}" \
    ../
cmake --build . -- -j4
