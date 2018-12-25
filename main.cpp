#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "snake/snake.cpp"

void glfwInitWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void processSnakeInput(GLFWwindow *window, Snake *snake);

int main() {
    glfwInitWindow();
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Snake *snake = new Snake();

    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        //testing input capturing for small snake game
        processSnakeInput(window, snake);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void glfwInitWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //this is only needed on Mac OS
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void processSnakeInput(GLFWwindow *window, Snake *snake) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        snake->setXVelocity(-1);
        std::cout << "left" << std::endl;
        std::cout << snake->xVelocity << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        snake->setXVelocity(1);
        std::cout << "right" << std::endl;
        std::cout << snake->xVelocity << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        snake->setYVelocity(-1);
        std::cout << "up" << std::endl;
        std::cout << snake->yVelocity << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        snake->setYVelocity(1);
        std::cout << "down" << std::endl;
        std::cout << snake->yVelocity << std::endl;
    }


    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        std::cout << "before adding + 1" << std::endl;
        snake->addToTail();
        std::cout << "adding + 1" << std::endl;
        std::cout << "size is now: " << snake->tailLength << std::endl;
    }
}