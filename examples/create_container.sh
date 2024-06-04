#!/bin/bash

host_uid=$(id -u)
host_gid=$(id -g)

# id=$(code --version | awk '/[a-f]/ {print $0}')
# echo $id

function db {
    tag=$1
    target=$tag
    docker build \
        --memory 1g \
        --build-arg HTTP_PROXY="http://192.168.1.1:3128" \
        --build-arg HTTPS_PROXY="http://192.168.1.1:3128" \
        --build-arg UID=$host_uid \
        --build-arg GID=$host_gid \
        --build-arg VSCODE_COMMIT_ID=$(code --version | awk '/[a-f]/ {print $0}') \
        --tag $tag \
        .
}

db "gcc"
