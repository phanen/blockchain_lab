
cmake_minimum_required(VERSION 3.10)
project(hash_collision)

add_library(base64 src/base64.cc)
target_include_directories(base64 PRIVATE ./include)

add_library(md5 src/md5.cc)
target_include_directories(md5 PRIVATE ./include)

add_library(sha1 src/sha1.cc)
target_include_directories(sha1 PRIVATE ./include)

add_executable(main src/main.cc)
target_link_libraries(main PRIVATE base64 md5 sha1)
target_include_directories(main PRIVATE ./include)