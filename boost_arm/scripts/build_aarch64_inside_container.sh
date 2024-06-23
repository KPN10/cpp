#!/bin/bash

gcc_version=$1
image_name="gcc_${gcc_version}_aarch64_boost"

file_path=$2
echo "file_path: ${file_path}"
filename_with_extension=$(basename ${file_path})
echo "filename_with_extension: ${filename_with_extension}"
filename=$(basename "${filename_with_extension}" | cut -d. -f1)
echo "filename: ${filename}"

output_filename=$3
workspace_folder=$4
echo "workspace_folder: ${workspace_folder}"
workspace_path_inside_container="/home/developer/workspace"

current_dir=$(pwd)
echo "current_dir: ${current_dir}"

workspace_file_path="${current_dir#"$workspace_folder"}"
echo "workspace_file_path: ${workspace_file_path}"

docker run \
  -it \
  --rm \
  -v $workspace_folder:$workspace_path_inside_container \
  $image_name \
  /bin/bash ${workspace_path_inside_container}/scripts/build_aarch64.sh $gcc_version \
  "${workspace_path_inside_container}/${workspace_file_path}/${filename_with_extension}" \
  "${workspace_path_inside_container}/${workspace_file_path}/${filename}_aarch64"
