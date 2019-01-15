cmake_minimum_required(VERSION 3.12)
project(OpenGLTest)

#set(SOURCE_FILES glad.c 01_GettingStarted/03_HelloWindow/main.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/04_HelloTriangle/main1.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/04_HelloTriangle/main2.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/05_Shaders/main1.cpp)
set(SOURCE_FILES glad.c 01_GettingStarted/05_Shaders/main2.cpp)
#set(SOURCE_FILES glad.c main.cpp)
set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGLTest glad.c
        #snake/snake.cpp
        #01_GettingStarted/03_HelloWindow/main.cpp
        #01_GettingStarted/04_HelloTriangle/main1.cpp
        #01_GettingStarted/04_HelloTriangle/main2.cpp
#        01_GettingStarted/05_Shaders/main1.cpp
        01_GettingStarted/05_Shaders/main2.cpp
        )

target_link_libraries(OpenGLTest GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp)
