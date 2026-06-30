cmake_minimum_required(VERSION 3.27)
project(SDLProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        Core/Actor/Actor.h
        Core/Actor/Actor.cpp
        Utils/Utils.h
        Core/Math/Vector2.h
        Core/Math/Math.h
        Core/Game/Game.h
        Core/Game/Game.cpp
        Core/Renderer/Renderer.h)

set(SDL3_DIR "C:/SDL3-3")

list(APPEND CMAKE_PREFIX_PATH "${SDL3_DIR}")

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endif ()