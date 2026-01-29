cmake_minimum_required(VERSION 3.28)
project(alyacup LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

add_executable(main WIN32 src/main.cpp src/imageController.cpp include/imageController.h include/utils.h src/resource.rc)

target_link_libraries(main PRIVATE gdiplus)
target_compile_features(main PRIVATE cxx_std_20)
target_link_options(main PRIVATE -municode)

