cmake_minimum_required(VERSION 3.27)
project(SDLProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        Core/Actor/Actor.h
        Core/Actor/Actor.cpp
        Core/Math/Vector2.h
        Core/Math/Math.h
        Core/Game/Game.h
        Core/Game/Game.cpp
        Core/Renderer/Renderer.h
        Core/Inputs/InputManager.cpp
        Core/Inputs/InputManager.h
        Core/Camera/CameraComponent.h
        Core/Component/Component.cpp
        Core/Component/Component.h
        Core/Camera/CameraComponent.cpp
        Core/Texture/TextureManager.h
        Core/Layer/Layer.h
        Core/Camera/ClearFlags.h)

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

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_image::SDL3_image>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"  # ← fechado corretamente
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
endif()