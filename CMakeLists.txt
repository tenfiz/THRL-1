cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME THRL-1)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-pipe -O3")

add_executable(${PROJECT_NAME} main.cpp
        Renderer/ShaderProgram.cpp
        Renderer/ShaderProgram.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(_deps/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(_deps/glad)
target_link_libraries(${PROJECT_NAME} glad)