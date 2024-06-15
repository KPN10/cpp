#!/bin/bash

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
        --tag $tag \
        .
}

db "gcc_aarch64" "Dockerfile.aarch64"
