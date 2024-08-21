# Engine/CMakeLists.txt
cmake_minimum_required(VERSION 3.29)

add_library(Engine STATIC
        Include/Main/IProgram.h
        Src/Main/Application.cpp
        Include/Main/Application.h
        Src/Main/Window.cpp
        Include/Main/Window.h
        Include/Utility/Commons.h
        Include/Utility/Delegates.h
        Src/Main/IProgram.cpp
        Include/Utility/MathF.h
        Include/Systems/StateSystem.h
        Src/Systems/StateSystem.cpp
        Include/States/GameState.h
        Src/States/GameState.cpp
        Include/ECS/Entity.h
        Src/ECS/Entity.cpp
        Include/ECS/Components/Component.h
        Src/ECS/Components/Component.cpp
        Include/Utility/Utility.h
        Include/Graphics/Texture2D.h
        Src/Graphics/Texture2D.cpp
        Include/Graphics/AssetManager.h
        Src/Graphics/AssetManager.cpp
        Include/ECS/Components/SpriteRenderer.h
        Src/ECS/Components/SpriteRenderer.cpp
        Include/Graphics/Sprite.h
        Src/Graphics/Sprite.cpp
        Src/Utility/Utility.cpp
        Include/States/Level.h
        Src/States/Level.cpp
        Include/Systems/LevelManager.h
        Src/Systems/LevelManager.cpp
        Include/Systems/EntityManager.h
        Src/Systems/EntityManager.cpp
        Include/Graphics/SpriteSheet.h
        Src/Graphics/SpriteSheet.cpp
        Include/Systems/InputManager.h
        Src/Systems/InputManager.cpp
        Include/Rendering/Camera.h
        Src/Rendering/Camera.cpp
        Include/Utility/Constants.h
        Include/Rendering/Renderer.h
        Src/Rendering/Renderer.cpp
        Include/ECS/Components/Transform.h
        Src/ECS/Components/Transform.cpp
)

target_include_directories(Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/Engine/Include
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${JSONCPP_INCLUDE_DIRS}
)

target_link_libraries(Engine PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${JSONCPP_LIBRARY}
)