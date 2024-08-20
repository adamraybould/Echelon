cmake_minimum_required(VERSION 3.29)
project(Echelon)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "D:/Game Projects/C++/SDL2-2.30.6/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

find_package(JsonCpp REQUIRED)

add_subdirectory(Engine)
add_subdirectory(Game)