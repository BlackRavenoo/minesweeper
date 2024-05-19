cmake_minimum_required(VERSION 3.28)
project(minesweeper VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options(-Wall -Wextra)

add_link_options(-lraylib)

add_executable(minesweeper ${SOURCE_FILES})