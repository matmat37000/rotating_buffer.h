cmake_minimum_required(VERSION 3.23)

project(rottating-buffer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(rottating-buffer-demo)
target_sources(rottating-buffer-demo
  PRIVATE
  src/main.cpp
)
