cmake_minimum_required(VERSION 3.8)
project(Echelon)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/Assets/")
set(SCRIPTS_PATH "${CMAKE_SOURCE_DIR}/Scripts/")
set(VERSION "1.0.0")

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)

find_path(LUABRIDGE3_INCLUDE_DIRS "luabridge3/LuaBridge/Array.h")

find_package(ZLIB REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(crossguid CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

add_subdirectory(Engine)
add_subdirectory(Game)