# Game/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

add_executable(Game
        Src/Main.cpp
)

target_include_directories(Game PRIVATE
        ${CMAKE_SOURCE_DIR}/Game/Include
)

target_link_libraries(Game PRIVATE
        Engine
)