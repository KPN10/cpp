#!/bin/bash

host_uid=$(id -u)
host_gid=$(id -g)

cd ..

function db {
  tag=$1
  target=$tag
  docker build \
    -f $2 \
    --build-arg PROXY="http://192.168.1.1:3128" \
    --build-arg UID=$host_uid \
    --build-arg GID=$host_gid \
    --tag $tag \
    .
}

db "aarch64_qemu" "Dockerfile.aarch64-qemu"


