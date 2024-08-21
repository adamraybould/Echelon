# Engine/CMakeLists.txt
cmake_minimum_required(VERSION 3.29)

add_library(Engine STATIC
        Include/Engine/Core/IProgram.h
        Src/Core/Application.cpp
        Include/Engine/Core/Application.h
        Src/Core/Window.cpp
        Include/Engine/Core/Window.h
        Include/Engine/Utility/Commons.h
        Include/Engine/Utility/Delegates.h
        Src/Core/IProgram.cpp
        Include/Engine/Utility/MathF.h
        Include/Engine/Systems/StateSystem.h
        Src/Systems/StateSystem.cpp
        Include/Engine/States/GameState.h
        Src/States/GameState.cpp
        Include/Engine/Core/ECS/Entity.h
        Src/Core/ECS/Entity.cpp
        Include/Engine/Core/ECS/Components/Component.h
        Src/Core/ECS/Components/Component.cpp
        Include/Engine/Utility/Utility.h
        Include/Engine/Graphics/Texture2D.h
        Src/Graphics/Texture2D.cpp
        Include/Engine/Graphics/AssetManager.h
        Src/Graphics/AssetManager.cpp
        Include/Engine/Core/ECS/Components/SpriteRenderer.h
        Src/Core/ECS/Components/SpriteRenderer.cpp
        Include/Engine/Graphics/Sprite.h
        Src/Graphics/Sprite.cpp
        Src/Utility/Utility.cpp
        Include/Engine/States/Level.h
        Src/States/Level.cpp
        Include/Engine/Systems/LevelManager.h
        Src/Systems/LevelManager.cpp
        Include/Engine/Systems/EntityManager.h
        Src/Systems/EntityManager.cpp
        Include/Engine/Graphics/SpriteSheet.h
        Src/Graphics/SpriteSheet.cpp
        Include/Engine/Systems/InputManager.h
        Src/Systems/InputManager.cpp
        Include/Engine/Rendering/Camera.h
        Src/Rendering/Camera.cpp
        Include/Engine/Utility/Constants.h
        Include/Engine/Rendering/Renderer.h
        Src/Rendering/Renderer.cpp
        Include/Engine/Core/ECS/Components/Transform.h
        Src/Core/ECS/Components/Transform.cpp
        Include/Engine/Core/Maths/Vector2.h
        Include/Engine/Core/Maths/Quaternion.h
        Include/Engine/Core/Maths/Rectangle.h
)

target_include_directories(Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/Engine/Include
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${JSONCPP_INCLUDE_DIRS}
        ${IMGUI_INCLUDE_DIR}
)

target_link_libraries(Engine PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${JSONCPP_LIBRARY}
        ${IMGUI_LIBRARY}
)