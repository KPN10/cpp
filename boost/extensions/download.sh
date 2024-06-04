#!/bin/bash

curl \
    --compressed \
    --proxy "http://192.168.1.1:3128" \
    --output twxs.cmake-0.0.17.vsix \
    https://marketplace.visualstudio.com/_apis/public/gallery/publishers/twxs/vsextensions/cmake/0.0.17/vspackage \
    --output ms-vscode.cmake-tools-1.18.41.vsix \
    https://marketplace.visualstudio.com/_apis/public/gallery/publishers/ms-vscode/vsextensions/cmake-tools/1.18.41/vspackage \
    --output ms-vscode.cpptools-1.20.5@linux-x64.vsix \
    https://marketplace.visualstudio.com/_apis/public/gallery/publishers/ms-vscode/vsextensions/cpptools/1.20.5/vspackage?targetPlatform=linux-x64 \
    --output ms-vscode.cpptools-extension-pack-1.3.0.vsix \
    https://marketplace.visualstudio.com/_apis/public/gallery/publishers/ms-vscode/vsextensions/cpptools-extension-pack/1.3.0/vspackage \
    --output ms-azuretools.vscode-docker-1.29.1.vsix \
    https://marketplace.visualstudio.com/_apis/public/gallery/publishers/ms-azuretools/vsextensions/vscode-docker/1.29.1/vspackage
