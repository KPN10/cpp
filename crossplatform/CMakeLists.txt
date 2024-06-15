cmake_minimum_required(VERSION 3.10)

# set(CMAKE_CXX_COMPILER /home/developer/toolchain/arm-gnu-toolchain-12.3.rel1-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++)
set(project_name "app")
project(${project_name})
add_executable(${project_name} sources/main.cpp)
