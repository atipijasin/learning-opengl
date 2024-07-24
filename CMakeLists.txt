cmake_minimum_required(VERSION 3.10)
project(learning-opengl)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(SYSTEM external/glad/include)

add_executable(
  learning-opengl
  src/initializeWindow.cpp
  src/main.cpp
  external/glad/src/glad.c
)

target_link_libraries(learning-opengl glfw OpenGL::GL)
