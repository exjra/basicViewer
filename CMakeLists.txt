cmake_minimum_required(VERSION 3.5)

project(basicViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ADEV_DIR ${CMAKE_SOURCE_DIR}/..)

add_definitions(-DADEV_DIR=$CMAKE_SOURCE_DIR)

include_directories(${ADEV_DIR}/cots/glew/include)
include_directories(${ADEV_DIR}/cots/glfw/include)
include_directories(${ADEV_DIR}/cots/glm)
include_directories(${ADEV_DIR}/src)

message(${ADEV_DIR})

add_executable(basicViewer
    main.cpp
    acontroller.cpp
    core/aiprocessor.cpp
    helpers/ahelpers.cpp
    helpers/acmdlineparser.cpp
    renderer/arenderer.cpp
    window/awindow.cpp
    renderer/mesh.cpp
    renderer/shader.cpp
    renderer/texture.cpp
    )

target_link_directories(basicViewer PUBLIC ${ADEV_DIR}/cots/glew/lib/Release/x64)
target_link_directories(basicViewer PUBLIC ${ADEV_DIR}/cots/glfw/lib-vc2019)

IF (WIN32)
    target_link_libraries(basicViewer PUBLIC setupapi Advapi32 Shell32 wbemuuid opengl32 glew32 glfw3dll)
ELSE()
    target_link_libraries(basicViewer PUBLIC pthread)
ENDIF()
