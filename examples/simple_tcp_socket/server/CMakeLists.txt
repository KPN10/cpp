cmake_minimum_required(VERSION 3.10)

set(project_name "server")
project(${project_name})
add_executable(${project_name} sources/main.cpp sources/server.hpp sources/server.cpp)
