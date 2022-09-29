
cmake_minimum_required(VERSION 3.10)
project(hash_collision)

add_executable(hash_collision src/base64.cc src/main.cc src/hash_collision.cc)

target_include_directories(hash_collision PRIVATE ./include)