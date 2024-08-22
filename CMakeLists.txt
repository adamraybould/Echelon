cmake_minimum_required(VERSION 3.8)
project(Echelon)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

find_package(ZLIB REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

add_subdirectory(Engine)
add_subdirectory(Game)