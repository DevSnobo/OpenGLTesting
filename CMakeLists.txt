cmake_minimum_required(VERSION 3.12)
project(OpenGLTest)

set(SOURCE_FILES glad.c main.cpp)
set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGLTest main.cpp glad.c snake/snake.cpp)
target_link_libraries(OpenGLTest GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp)