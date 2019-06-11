cmake_minimum_required(VERSION 3.12)
project(OpenGLTest)

include_directories(/usr/include/freetype2)

#set(SOURCE_FILES glad.c 01_GettingStarted/03_HelloWindow/main.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/04_HelloTriangle/main1.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/04_HelloTriangle/main2.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/05_Shaders/main1.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/05_Shaders/main2.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/06_Textures/main1.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/06_Textures/main2.cpp)
#set(SOURCE_FILES glad.c 01_GettingStarted/00_Test/test.cpp)
#set(SOURCE_FILES glad.c tictactoe/tictactoe.cpp)
#set(SOURCE_FILES glad.c main.cpp)
set(SOURCE_FILES glad.c 0X_InPractice/main.cpp
        0X_InPractice/game.cpp
        0X_InPractice/shader.cpp
        0X_InPractice/texture.cpp
        0X_InPractice/text.cpp
        0X_InPractice/resource_manager.cpp
        0X_InPractice/sprite_renderer.cpp
        0X_InPractice/text_renderer.cpp
        0X_InPractice/renderer.cpp
        0X_InPractice/game_object.cpp
        0X_InPractice/ball_object.cpp
        0X_InPractice/game_level.cpp
        0X_InPractice/menu.cpp
        0X_InPractice/ui.cpp
        0X_InPractice/ui_renderer.cpp
        )
set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGLTest glad.c glm
        #snake/snake.cpp
        #01_GettingStarted/03_HelloWindow/main.cpp
        #01_GettingStarted/04_HelloTriangle/main1.cpp
        #01_GettingStarted/04_HelloTriangle/main2.cpp
#        01_GettingStarted/05_Shaders/main1.cpp
#        01_GettingStarted/05_Shaders/main2.cpp
#        01_GettingStarted/06_Textures/main1.cpp
#        01_GettingStarted/06_Textures/main2.cpp
        #01_GettingStarted/00_Test/test.cpp
#        tictactoe/tictactoe.cpp
        #Shader.h
        stb_image.cpp
        0X_InPractice/main.cpp
        0X_InPractice/game.h 0X_InPractice/game.cpp
        0X_InPractice/shader.h 0X_InPractice/shader.cpp
        0X_InPractice/texture.h 0X_InPractice/texture.cpp
        0X_InPractice/text.h 0X_InPractice/text.cpp
        0X_InPractice/resource_manager.h 0X_InPractice/resource_manager.cpp
        0X_InPractice/sprite_renderer.h 0X_InPractice/sprite_renderer.cpp
        0X_InPractice/text_renderer.h 0X_InPractice/text_renderer.cpp
        0X_InPractice/game_object.h 0X_InPractice/game_object.cpp
        0X_InPractice/game_level.h 0X_InPractice/game_level.cpp
        0X_InPractice/ball_object.h 0X_InPractice/ball_object.cpp
        0X_InPractice/menu.h 0X_InPractice/menu.cpp
        0X_InPractice/renderer.h 0X_InPractice/renderer.cpp
        0X_InPractice/ui.cpp 0X_InPractice/ui.h
        0X_InPractice/ui_renderer.cpp 0X_InPractice/ui_renderer.h)

target_link_libraries(OpenGLTest GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp freetype)
