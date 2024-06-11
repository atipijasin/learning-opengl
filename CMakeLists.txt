cmake_minimum_required(VERSION 3.10)
project(learning-opengl)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(learning-opengl main.cpp)
target_link_libraries(learning-opengl glfw OpenGL::GL)
