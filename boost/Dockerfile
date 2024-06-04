FROM ubuntu:22.04
ARG HTTP_PROXY
ARG HTTPS_PROXY
ARG BOOST_VERSION_MAJOR
ARG BOOST_VERSION_MINOR
ARG BOOST_VERSION_PATCH
ARG VSCODE_COMMIT_ID
ARG UID
ARG GID
RUN apt update && apt upgrade -y
RUN apt install sudo gcc g++ gdb cmake make git curl -y
RUN addgroup -gid $GID nonroot && \
    echo 'developer ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers && \
    useradd -m --uid $UID --gid $GID -s /bin/bash developer && \
    usermod -aG sudo developer && \
    chown -R developer:nonroot /home/developer && \
    chmod -R 755 /home/developer
USER developer
WORKDIR /home/developer

RUN curl --proxy $HTTP_PROXY \
    -fsSL "https://update.code.visualstudio.com/commit:${VSCODE_COMMIT_ID}/server-linux-x64/stable" \
    -o /home/developer/vscode-server-linux-x64.tar.gz && \
    mkdir -p ~/.vscode-server/bin/$VSCODE_COMMIT_ID && \
    tar zxvf ~/vscode-server-linux-x64.tar.gz \
    -C ~/.vscode-server/bin/$VSCODE_COMMIT_ID --strip 1 && \
    rm ~/vscode-server-linux-x64.tar.gz && \
    touch ~/.vscode-server/bin/$VSCODE_COMMIT_ID/0

# COPY extensions/* /home/developer
# RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
#     --install-extension ~/twxs.cmake-0.0.17.vsix
# RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
#     --install-extension ~/ms-vscode.cpptools-extension-pack-1.3.0.vsix
# RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
#     --install-extension ~/ms-vscode.cpptools-1.20.5@linux-x64.vsix
# RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
#     --install-extension ~/ms-vscode.cmake-tools-1.18.41.vsix
# RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
#     --install-extension ~/ms-azuretools.vscode-docker-1.29.1.vsix
RUN curl \
    --compressed \
    --proxy $HTTP_PROXY \
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

RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
    --install-extension ~/twxs.cmake-0.0.17.vsix
RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
    --install-extension ~/ms-vscode.cpptools-extension-pack-1.3.0.vsix
RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
    --install-extension ~/ms-vscode.cpptools-1.20.5@linux-x64.vsix
RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
    --install-extension ~/ms-vscode.cmake-tools-1.18.41.vsix
RUN ~/.vscode-server/bin/${VSCODE_COMMIT_ID}/bin/code-server \
    --install-extension ~/ms-azuretools.vscode-docker-1.29.1.vsix
RUN rm -dRf *.vsix

ENV BOOST_VERSION=${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}_${BOOST_VERSION_PATCH}
RUN curl --proxy $HTTP_PROXY \
    "https://archives.boost.io/release/${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_PATCH}/source/boost_${BOOST_VERSION}.tar.gz" \
    -o /home/developer/boost_${BOOST_VERSION}.tar.gz && \
    tar -xvzf boost_${BOOST_VERSION}.tar.gz && \
    cd boost_${BOOST_VERSION} && \
    ./bootstrap.sh && \
    sudo ./b2 install --prefix=/opt/boost && \
    cd /home/developer && \
    sudo rm -dRf boost_${BOOST_VERSION} && \
    rm boost_${BOOST_VERSION}.tar.gz
