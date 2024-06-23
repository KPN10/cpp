#!/bin/bash

workspace_path="/home/developer/workspace"
gcc_version=$1
image_name="gcc_${gcc_version}_aarch64"
current_dir=$(pwd)
workspace_path_host=$(dirname $current_dir)

docker run \
  -it \
  --rm \
  -v $workspace_path_host: \
  $image_name \
  /bin/bash ${workspace_path}/scripts/build_aarch64.sh $gcc_version
