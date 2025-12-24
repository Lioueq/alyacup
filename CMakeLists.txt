cmake_minimum_required(VERSION 4.1)
project(re_alyacup)


set(CMAKE_CXX_STANDARD 20)

add_executable(re_alyacup main.cpp)

target_link_options(re_alyacup PRIVATE -municode)