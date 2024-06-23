#!/bin/bash

arm_gcc_version=$1
boost_version_major=1
boost_version_minor=85
boost_version_patch=0

host_uid=$(id -u)
host_gid=$(id -g)

if [ "${arm_gcc_version}" == "10.3" ]; then
  arm_gcc_link="https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu.tar.xz"
  arm_gcc_name="gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu"
  arm_gcc_name_tar="${arm_gcc_name}.tar.xz"
elif [ "${arm_gcc_version}" == "13.2" ]; then
  arm_gcc_link="https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz"
  arm_gcc_name="arm-gnu-toolchain-13.2.rel1-x86_64-aarch64-none-linux-gnu"
  arm_gcc_name_tar="${arm_gcc_name}.tar.xz"
else
  arm_gcc_link="n/a"
  arm_gcc_name="n/a"
  arm_gcc_name_tar="n/a"
fi

cd ..

function db {
  tag=$1
  target=$tag
  docker build \
    -f $2 \
    --build-arg PROXY="http://192.168.1.1:3128" \
    --build-arg BOOST_VERSION_MAJOR=$boost_version_major \
    --build-arg BOOST_VERSION_MINOR=$boost_version_minor \
    --build-arg BOOST_VERSION_PATCH=$boost_version_patch \
    --build-arg UID=$host_uid \
    --build-arg GID=$host_gid \
    --build-arg ARM_GCC_LINK=$arm_gcc_link \
    --build-arg ARM_GCC_NAME=$arm_gcc_name \
    --build-arg ARM_GCC_NAME_TAR=$arm_gcc_name_tar \
    --tag $tag \
    .
}

db "gcc_${arm_gcc_version}_aarch64_boost" "Dockerfile.aarch64"

