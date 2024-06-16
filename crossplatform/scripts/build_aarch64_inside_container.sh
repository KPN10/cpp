#!/bin/bash

gcc_version=$1
image_name="gcc_${gcc_version}_aarch64"
current_dir=$(pwd)
workspace_path=$(dirname $current_dir)
# echo $workspace_path

docker run \
    -it \
    --rm \
    -v $workspace_path:/home/developer/workspace \
    $image_name \
    /bin/bash /home/developer/workspace/scripts/build_aarch64.sh $gcc_version
