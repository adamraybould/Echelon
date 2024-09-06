# Game/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

add_executable(Echelon ${CMAKE_SOURCE_DIR}/Engine/Src/Core/Main.cpp)
target_link_libraries(Echelon PRIVATE Engine)