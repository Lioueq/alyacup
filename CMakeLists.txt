cmake_minimum_required(VERSION 3.28)
project(alyacup LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(main src/main.cpp)

target_compile_features(main PRIVATE cxx_std_20)

