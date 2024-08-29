# Engine/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

include(FindLua)

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
        Include/Engine/Core/Systems/StateSystem.h
        Src/Core/Systems/StateSystem.cpp
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
        Include/Engine/States/Level.h
        Src/States/Level.cpp
        Include/Engine/Core/Systems/LevelManager.h
        Src/Core/Systems/LevelManager.cpp
        Include/Engine/Core/Systems/EntityManager.h
        Src/Core/Systems/EntityManager.cpp
        Include/Engine/Graphics/SpriteSheet.h
        Src/Graphics/SpriteSheet.cpp
        Include/Engine/Core/Systems/InputManager.h
        Src/Core/Systems/InputManager.cpp
        Include/Engine/Core/Camera.h
        Src/Core/Camera.cpp
        Include/Engine/Utility/Constants.h
        Include/Engine/Core/Renderer.h
        Src/Core/Renderer.cpp
        Include/Engine/Core/ECS/Components/Transform.h
        Src/Core/ECS/Components/Transform.cpp
        Include/Engine/Core/Maths/Vector2.h
        Include/Engine/Core/Maths/Quaternion.h
        Include/Engine/Core/Maths/Rectangle.h
        Include/Engine/Core/Editor/EngineGUI.h
        Src/Core/Editor/EngineGUI.cpp
        Include/Engine/Core/Editor/GUIWindow.h
        Include/Engine/Core/Editor/Windows/GUIWindow_EntityInfo.h
        Src/Core/Editor/Windows/GUIWindow_EntityInfo.cpp
        Src/Core/Scripting/ScriptCore.cpp
        Include/Engine/Core/Scripting/ScriptCore.h
        Include/Engine/Core/Scripting/IBinder.h
        Src/Core/Scripting/IBinder.cpp
        Include/Engine/Core/Scripting/EntityInterface.h
        Include/Engine/Core/Scripting/Prefab.h
        Src/Core/Scripting/Prefab.cpp
        Include/Engine/Core/Engine.h
        Src/Core/Engine.cpp
        Include/Engine/Core/Input.h
        Src/Core/Input.cpp
        Include/Engine/Graphics/TileMap.h
        Src/Graphics/TileMap.cpp
        Include/Engine/Graphics/MapLayer.h
        Src/Graphics/MapLayer.cpp
)

target_include_directories(Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/Engine/Include
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/vcpkg_installed/x86-mingw-dynamic/include
        ${LUABRIDGE3_INCLUDE_DIRS}
)

target_include_directories(Engine PRIVATE
        ${CMAKE_BINARY_DIR}
        ${TMXLITE_INCLUDE_DIR}
)

target_link_libraries(Engine PRIVATE ${LUA_LIBRARIES})
target_link_libraries(Engine PRIVATE ZLIB::ZLIB)
target_link_libraries(Engine PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
target_link_libraries(Engine PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(Engine PRIVATE imgui::imgui)
target_link_libraries(Engine PRIVATE JsonCpp::JsonCpp)
target_link_libraries(Engine PRIVATE ${LUA_LIBRARIES})
target_link_libraries(Engine PRIVATE crossguid)
target_link_libraries(Engine PRIVATE magic_enum::magic_enum)
target_link_libraries(Engine PRIVATE ${TMXLITE_LIBRARY})
