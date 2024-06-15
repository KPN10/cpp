#!/bin/bash

image_name="gcc"
current_dir=$(pwd)
workspace_path=$(dirname $current_dir)
# echo $workspace_path

docker run \
    -it \
    --rm \
    -v $workspace_path:/home/developer/workspace \
    $image_name \
    /bin/bash /home/developer/workspace/scripts/build_x86_64.sh
