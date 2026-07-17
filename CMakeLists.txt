cmake_minimum_required(VERSION 3.27)
project(SDLProject)

set(CMAKE_CXX_STANDARD 23)

set(ENGINE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Engine")
set(USER_PROJECT_DIR "${CMAKE_SOURCE_DIR}/Sandbox")

option(BUILD_WITH_EDITOR "Compile with Editor Support" ON)

file(GLOB_RECURSE COMPONENT_HEADERS CONFIGURE_DEPENDS
        "${ENGINE_SOURCE_DIR}/*.h"
        "${USER_PROJECT_DIR}/*.h"
)

include(FetchContent)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)
FetchContent_MakeAvailable(box2d)

set(CORE_SOURCES
        main.cpp
        Engine/Engine.h
        Engine/Engine.cpp
        Engine/Game/Game.h
        Engine/Game/Game.cpp

        Engine/Game/Core/Actor/Actor.h
        Engine/Game/Core/Math/Vector2.h
        Engine/Game/Core/Math/Math.h
        Engine/Game/Core/Color/Color.h
        Engine/Game/Core/Shape/Shape.h
        Engine/Game/Core/Transform/Transform.h

        Engine/Game/Core/Renderer/Renderer.h
        Engine/Game/Core/RenderType/RenderType.h
        Engine/Game/Core/RenderType/ShapeRender.cpp
        Engine/Game/Core/RenderType/ShapeRender.h

        Engine/Game/Core/Inputs/InputManager.cpp
        Engine/Game/Core/Inputs/InputManager.h

        Engine/Game/Core/Component/Component.cpp
        Engine/Game/Core/Component/Component.h
        Engine/Game/Core/Camera/CameraComponent.h
        Engine/Game/Core/Camera/CameraComponent.cpp
        Engine/Game/Core/Camera/ClearFlags.h

        Engine/Game/Core/Texture/TextureManager.h
        Engine/Game/Core/Layer/Layer.h

        Engine/Game/Core/Scene/Scene.cpp
        Engine/Game/Core/Scene/Scene.h

        Engine/Game/Core/Serialization/SceneSerializer/SceneSerializer.cpp
        Engine/Game/Core/Serialization/SceneSerializer/SceneSerializer.h
        Engine/Game/Core/Factory/Factory.h
        Engine/Game/Core/Reflection/PropertyType/PropertyType.h
        Engine/Game/Core/Macros/EngineMacros.h

        Engine/ThirdParty/json.hpp
        Engine/ThirdParty/portable-file-dialogs.h
)

set(EDITOR_SOURCES
        Engine/Editor/Editor.cpp
        Engine/Editor/Editor.h
        Engine/Editor/Camera/EditorCamera.cpp
        Engine/Editor/Camera/EditorCamera.h

        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_sdl3.cpp
        imgui/backends/imgui_impl_sdlrenderer3.cpp
)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(GENERATED_FILES ""
        Engine/Game/Core/Macros/EngineMacros.h
        Sandbox/Assets/Scripts/GameplayScene.h
        Sandbox/Assets/Scripts/Player.h
        Sandbox/Assets/Scripts/WeaponComponent.h
        Sandbox/Assets/Scripts/Bullet.h
        Sandbox/Assets/Premades/Premades.h
        Engine/Game/Core/Camera/Follow/InstantFollow.h
        Engine/Game/Core/Camera/Follow/FollowStrategy.h
        Engine/Game/Core/Camera/Follow/LookAheadFollow.h
        Engine/Game/Core/Camera/Follow/SmoothFollow.h
        Sandbox/Assets/Scripts/BulletStrategy.h
        Sandbox/Assets/Scripts/DamageStrategy.h
        Engine/Game/Core/Movement/ProjectileMovementComponent.h
        Engine/Game/Core/Movement/ProjectileMovementComponent.cpp
        Sandbox/Assets/Scripts/WeaponComponent.cpp
        Engine/Game/Core/Utils/DestroyActorAfterTime.h
        Sandbox/Assets/Scripts/Entity.h
        Sandbox/Assets/Scripts/Weapon.cpp
        Sandbox/Assets/Scripts/Player.cpp
        Engine/Game/Core/Collision/Collider.cpp
        Engine/Game/Core/Collision/Collider.h
        Engine/Game/Core/Physics/PhysicsCore.h
        Engine/Game/Core/Physics/PhyscsManager.h
        Engine/Game/Core/Rigidbody/Rigidbody.h
        Engine/Game/Core/Rigidbody/Rigidbody.cpp)

foreach (HEADER ${COMPONENT_HEADERS})
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${HEADER})
    get_filename_component(REL_DIR ${REL_PATH} DIRECTORY)
    get_filename_component(BASENAME ${HEADER} NAME_WE)
    set(GENERATED_FILE "${CMAKE_CURRENT_BINARY_DIR}/generated/${REL_DIR}/${BASENAME}.generated.cpp")
    get_filename_component(GEN_DIR ${GENERATED_FILE} DIRECTORY)
    file(MAKE_DIRECTORY ${GEN_DIR})

    add_custom_command(
            OUTPUT ${GENERATED_FILE}
            COMMAND Python3::Interpreter ${CMAKE_SOURCE_DIR}/HeaderTool.py ${HEADER} ${GENERATED_FILE}
            DEPENDS ${HEADER} ${CMAKE_SOURCE_DIR}/HeaderTool.py
    )

    list(APPEND GENERATED_FILES ${GENERATED_FILE})
endforeach ()

add_executable(${PROJECT_NAME} ${CORE_SOURCES} ${GENERATED_FILES})

if(BUILD_WITH_EDITOR)
    target_compile_definitions(${PROJECT_NAME} PRIVATE TR_EDITOR)
    target_sources(${PROJECT_NAME} PRIVATE ${EDITOR_SOURCES})
endif ()

target_compile_definitions(${PROJECT_NAME} PRIVATE
        PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
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
        box2d
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
        imgui
        imgui/backends
        ${CMAKE_CURRENT_BINARY_DIR}
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
            "${CMAKE_SOURCE_DIR}/Sandbox/Assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )

    if(BUILD_WITH_EDITOR)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/Engine/Editor/Fonts"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Editor/Fonts"
        )
    endif()
endif()