#!/bin/bash

BOOST_VERSION_MAJOR=1
BOOST_VERSION_MINOR=85
BOOST_VERSION_PATCH=0
BOOST_VERSION=$BOOST_VERSION_MAJOR_$BOOST_VERSION_MINOR_$BOOST_VERSION_PATCH

host_uid=$(id -u)
host_gid=$(id -g)

# id=$(code --version | awk '/[a-f]/ {print $0}')
# echo $id

function db {
    tag=$1
    target=$tag
    docker build \
        --build-arg PROXY="http://192.168.1.1:3128" \
        --build-arg BOOST_VERSION_MAJOR=$BOOST_VERSION_MAJOR \
        --build-arg BOOST_VERSION_MINOR=$BOOST_VERSION_MINOR \
        --build-arg BOOST_VERSION_PATCH=$BOOST_VERSION_PATCH \
        --build-arg UID=$host_uid \
        --build-arg GID=$host_gid \
        --build-arg VSCODE_COMMIT_ID=$(code --version | awk '/[a-f]/ {print $0}') \
        --tag $tag \
        .
}

db "gcc_boost_${BOOST_VERSION}"

