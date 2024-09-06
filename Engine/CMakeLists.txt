# Engine/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

include(FindLua)

add_library(Engine STATIC
        Include/Core/IProgram.h
        Src/Core/Application.cpp
        Include/Core/Application.h
        Src/Core/IO/Window.cpp
        Include/Core/IO/Window.h
        Include/Core/Commons.h
        Include/Core/Delegates.h
        Src/Core/IProgram.cpp
        Include/Core/Maths/MathF.h
        Include/Systems/StateSystem.h
        Src/Systems/StateSystem.cpp
        Include/States/GameState.h
        Src/States/GameState.cpp
        Include/Scene/Entities/Entity.h
        Src/Scene/Entities/Entity.cpp
        Include/Scene/Entities/Components/Component.h
        Src/Scene/Entities/Components/Component.cpp
        Include/Core/Utility.h
        Include/Graphics/Texture2D.h
        Src/Graphics/Texture2D.cpp
        Include/Core/AssetManager.h
        Src/Core/AssetManager.cpp
        Include/Scene/Entities/Components/SpriteRenderer.h
        Src/Scene/Entities/Components/SpriteRenderer.cpp
        Include/Graphics/Sprite.h
        Src/Graphics/Sprite.cpp
        Include/States/Level.h
        Src/States/Level.cpp
        Include/Systems/LevelManager.h
        Src/Systems/LevelManager.cpp
        Include/Systems/EntityManager.h
        Src/Systems/EntityManager.cpp
        Include/Graphics/SpriteSheet.h
        Src/Graphics/SpriteSheet.cpp
        Include/Core/Camera.h
        Src/Core/Camera.cpp
        Include/Core/Constants.h
        Include/Core/IO/Renderer.h
        Src/Core/IO/Renderer.cpp
        Include/Scene/Entities/Components/Transform.h
        Src/Scene/Entities/Components/Transform.cpp
        Include/Core/Maths/Vector2.h
        Include/Core/Maths/Rectangle.h
        Include/Editor/EngineGUI.h
        Src/Editor/EngineGUI.cpp
        Include/Editor/GUIWindow.h
        Include/Editor/Windows/GUIWindow_EntityInfo.h
        Src/Editor/Windows/GUIWindow_EntityInfo.cpp
        Src/Core/Scripting/ScriptCore.cpp
        Include/Core/Scripting/ScriptCore.h
        Include/Core/Scripting/IBinder.h
        Src/Core/Scripting/IBinder.cpp
        Include/Core/Scripting/EntityInterface.h
        Include/Core/Scripting/Prefab.h
        Src/Core/Scripting/Prefab.cpp
        Include/Core/Scripting/Engine.h
        Src/Core/Scripting/Engine.cpp
        Include/Core/IO/Input.h
        Src/Core/IO/Input.cpp
        Include/Graphics/TileMap/TileMap.h
        Src/Graphics/TileMap/TileMap.cpp
        Include/Graphics/TileMap/MapLayer.h
        Src/Graphics/TileMap/MapLayer.cpp
        Include/Core/IO/IRenderable.h
        Include/Scene/Entities/Components/Rigidbody.h
        Src/Scene/Entities/Components/Rigidbody.cpp
        Include/Core/Physics.h
        Src/Core/Physics.cpp
        Include/Graphics/TileMap/ObjectLayer.h
        Src/Graphics/TileMap/ObjectLayer.cpp
        Include/Debugging/DebugDraw.h
        Src/Debugging/DebugDraw.cpp
        Include/Scene/Entities/Components/Animator.h
        Src/Scene/Entities/Components/Animator.cpp
        Include/Graphics/Animation.h
        Src/Editor/GUIWindow.cpp
        Include/Graphics/TileMap/Tile.h
        Src/Graphics/TileMap/Tile.cpp
        Include/Core/Audio/AudioSystem.h
        Src/Core/Audio/AudioSystem.cpp
        Include/Scene/Entities/Components/SoundEmitter.h
        Src/Scene/Entities/Components/SoundEmitter.cpp
        Include/Core/TypeDefs.h
        Include/Core/Audio/AudioBank.h
        Src/Core/Audio/AudioBank.cpp
        Src/Core/Audio/AudioEvent.cpp
        Include/Core/Audio/AudioEvent.h
        Include/Core/System.h
        Src/Core/System.cpp
)

target_include_directories(Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/Engine/Include
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/vcpkg_installed/x86-mingw-dynamic/include
        ${LUABRIDGE3_INCLUDE_DIRS}
        ${FMOD_INCLUDE_DIR}
        ${FMOD_STUDIO_INCLUDE_DIR}
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
target_link_libraries(Engine PRIVATE box2d::box2d)
target_link_libraries(Engine PRIVATE ${FMOD_LIBRARIES})
target_link_libraries(Engine PRIVATE ${FMOD_STUDIO_LIBRARIES})
