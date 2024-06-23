#!/bin/bash

image_name="aarch64_qemu"
workspace_folder="/home/kpn/workspaces/cpp/boost_arm/examples"
workspace_path_inside_container="/home/developer/workspace"


file_path=$1
# echo "file_path: ${file_path}"
filename_with_extension=$(basename ${file_path})
# echo "filename_with_extension: ${filename_with_extension}"
filename=$(basename "${filename_with_extension}" | cut -d. -f1)
# echo "filename: ${filename}"

current_dir=$(pwd)
# echo "current_dir: ${current_dir}"
workspace_file_path="${current_dir#"$workspace_folder"}"
# echo "workspace_file_path: ${workspace_file_path}"

docker run \
  -it \
  --rm \
  -v $workspace_folder:$workspace_path_inside_container \
  $image_name \
  /bin/bash -c "qemu-aarch64-static ${workspace_path_inside_container}/${workspace_file_path}/${filename}_aarch64"
