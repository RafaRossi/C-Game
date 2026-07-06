cmake_minimum_required(VERSION 3.27)
project(SDLProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        ${PROJECT_NAME} main.cpp
        Engine/Game/Core/Actor/Actor.h
        Engine/Game/Core/Math/Vector2.h
        Engine/Game/Core/Math/Math.h
        Engine/Game/Game.h
        Engine/Game/Game.cpp
        Engine/Game/Core/Renderer/Renderer.h
        Engine/Game/Core/Inputs/InputManager.cpp
        Engine/Game/Core/Inputs/InputManager.h
        Engine/Game/Core/Camera/CameraComponent.h
        Engine/Game/Core/Component/Component.cpp
        Engine/Game/Core/Component/Component.h
        Engine/Game/Core/Camera/CameraComponent.cpp
        Engine/Game/Core/Texture/TextureManager.h
        Engine/Game/Core/Layer/Layer.h
        Engine/Game/Core/Camera/ClearFlags.h

        Engine/Editor/imgui/imgui.cpp
        Engine/Editor/imgui/imgui_draw.cpp
        Engine/Editor/imgui/imgui_tables.cpp
        Engine/Editor/imgui/imgui_widgets.cpp
        Engine/Editor/imgui/imgui_demo.cpp
        Engine/Editor/imgui/backends/imgui_impl_sdl3.cpp
        Engine/Editor/imgui/backends/imgui_impl_sdlrenderer3.cpp
        Engine/Editor/Editor.cpp
        Engine/Editor/Editor.h
        Engine/Editor/Reflection/Reflection.h
        Engine/Game/Core/Transform/Transform.cpp
        Engine/Game/Core/Transform/Transform.h
        Engine/Engine.h
        Engine/Engine.cpp
        Engine/Editor/Camera/EditorCamera.cpp
        Engine/Editor/Camera/EditorCamera.h
        Engine/Game/Core/Scene/Scene.cpp
        Engine/Game/Core/Scene/Scene.h
        Engine/Editor/Macros/EngineMacros.h
)

set(SDL3_DIR "C:/SDL3-3")
list(APPEND CMAKE_PREFIX_PATH "${SDL3_DIR}")
find_package(SDL3 REQUIRED CONFIG)

set(SDL3_image_DIR "C:/SDL3_image-3/cmake")
list(APPEND CMAKE_PREFIX_PATH "${SDL3_image_DIR}")
find_package(SDL3_image REQUIRED CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)

target_include_directories(${PROJECT_NAME} PRIVATE
        Engine/Editor/imgui
        Engine/Editor/imgui/backends
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_image::SDL3_image>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Engine/Editor/Fonts"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Editor/Fonts"
    )
endif()