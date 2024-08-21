# Game/CMakeLists.txt
cmake_minimum_required(VERSION 3.29)

add_executable(Game
        Echelon/Src/Main.cpp
        Echelon/Include/Entities/PlayerCharacter.h
        Echelon/Src/Entities/PlayerCharacter.cpp
        Echelon/Include/Levels/MainLevel.h
        Echelon/Src/Levels/MainLevel.cpp
        Echelon/Include/Entities/Components/PlayerController.h
        Echelon/Src/Entities/Components/PlayerController.cpp
        Echelon/Include/Entities/BlankCharacter.h
        Echelon/Src/Entities/BlankCharacter.cpp
        Echelon/Include/Entities/Components/CameraFollow.h
        Echelon/Src/Entities/Components/CameraFollow.cpp
)

target_include_directories(Game PRIVATE
        ${CMAKE_SOURCE_DIR}/Game/Echelon/Include
)

target_link_libraries(Game PRIVATE
        Engine
)