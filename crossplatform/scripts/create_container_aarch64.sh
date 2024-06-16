#!/bin/bash

arm_gcc_version=$1

if [ "${arm_gcc_version}" == "10.3" ]; then
    arm_gcc_link="https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu.tar.xz"
    arm_gcc_name="gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu"
    arm_gcc_name_tar="${arm_gcc_name}.tar.xz"
elif [ "${arm_gcc_version}" == "11.2" ]; then
    arm_gcc_link="https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/11.2-2022.02/binrel/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu.tar.xz"
    arm_gcc_name="gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu"
    arm_gcc_name_tar="${arm_gcc_name}.tar.xz"
elif [ "${arm_gcc_version}" == "12.3" ]; then
    arm_gcc_link="https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/12.3.rel1/binrel/arm-gnu-toolchain-12.3.rel1-x86_64-aarch64-none-linux-gnu.tar.xz"
    arm_gcc_name="arm-gnu-toolchain-12.3.rel1-x86_64-aarch64-none-linux-gnu"
    arm_gcc_name_tar="${arm_gcc_name}.tar.xz"
else
    arm_gcc_link="n/a"
    arm_gcc_name="n/a"
    arm_gcc_name_tar="n/a"
fi

host_uid=$(id -u)
host_gid=$(id -g)

# id=$(code --version | awk '/[a-f]/ {print $0}')
# echo $id
cd ..

function db {
    tag=$1
    target=$tag
    docker build \
        -f $2 \
        --build-arg HTTP_PROXY="http://192.168.1.1:3128" \
        --build-arg UID=$host_uid \
        --build-arg GID=$host_gid \
        --build-arg VSCODE_COMMIT_ID=$(code --version | awk '/[a-f]/ {print $0}') \
        --build-arg ARM_GCC_LINK=$arm_gcc_link \
        --build-arg ARM_GCC_NAME=$arm_gcc_name \
        --build-arg ARM_GCC_NAME_TAR=$arm_gcc_name_tar \
        --tag $tag \
        .
}

db "gcc_${arm_gcc_version}_aarch64" "Dockerfile.aarch64"
