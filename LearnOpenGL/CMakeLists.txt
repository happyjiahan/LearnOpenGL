﻿# CMakeList.txt : 顶级 CMake 项目文件，执行全局配置
# 和此处的包含子项目。
#
cmake_minimum_required (VERSION 3.8)
project ("LearnOpenGL")
set(CMAKE_CXX_STANDARD 11)

add_executable(LearnOpenGL src/main.cpp src/gl3w.c src/LoadShader.cpp)
message(${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/triangles.vert 
${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/triangles.frag 
${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_subdirectory(lib/glfw-3.2.1)
find_package(OpenGL REQUIRED)
include_directories(include lib/glfw-3.2.1/include)
target_link_libraries(LearnOpenGL glfw ${OPENGL_gl_LIBRARY})





