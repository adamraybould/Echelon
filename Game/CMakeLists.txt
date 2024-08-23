# Game/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

add_executable(Game
        Src/Main.cpp
        Include/Echelon/Entities/PlayerCharacter.h
        Src/Entities/PlayerCharacter.cpp
        Include/Echelon/Levels/MainLevel.h
        Src/Levels/MainLevel.cpp
        Include/Echelon/Entities/Components/PlayerController.h
        Src/Entities/Components/PlayerController.cpp
        Include/Echelon/Entities/BlankCharacter.h
        Src/Entities/BlankCharacter.cpp
        Include/Echelon/Entities/Components/CameraFollow.h
        Src/Entities/Components/CameraFollow.cpp
        Include/Echelon/Entities/Mobs/Gunbot.h
        Src/Entities/Mobs/Gunbot.cpp
        Include/Echelon/Entities/Mobs/Gunbot.h
        Include/Echelon/Entities/Mobs/DrillBot.h
        Src/Entities/Mobs/Drillbot.cpp
)

target_include_directories(Game PRIVATE
        ${CMAKE_SOURCE_DIR}/Game/Include
)

target_link_libraries(Game PRIVATE
        Engine
)