cmake_minimum_required(VERSION 3.23)

project(rotating-buffer LANGUAGES C)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(rotating-buffer-demo)
target_sources(rotating-buffer-demo
  PRIVATE
  src/main.c
)
