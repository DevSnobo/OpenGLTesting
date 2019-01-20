//
// Created by snobo on 1/15/19.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <iostream>
#include "../Shader.h"

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 ourColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   ourColor = aColor;\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(ourColor, 1.0f);\n"
                                   "}\n\0";

//class Square {
//    int height;
//    int width;
//    int xPosition;
//    int yPosition;
//};


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void eval_field(double coord, int *field) {

    if (0 <= coord && coord < 200)
        *field = 0;
    if (200 <= coord && coord < 400)
        *field = 1;
    if (400 <= coord && coord < 600)
        *field = 2;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);

        int xfield, yfield;

        eval_field(xpos, &xfield);
        eval_field(ypos, &yfield);

        std::cout << "Cursor Position at (" << xpos << " : " << ypos << ")" << std::endl;
        std::cout << "Cursor in Field (" << xfield << " : " << yfield << ")" << std::endl;
    }
}

int main() {

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // gflw callback functions
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("../shaders/3.3.shader.vs", "../shaders/3.3.shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices_white[] = {
            //first row             //color
            -1.0f, 1.0f, 0.0f,      1.0f, 1.0f, 1.0f,
            -0.33f, 1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
            0.33f, 1.0f, 0.0f,      1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f,       1.0f, 1.0f, 1.0f,

            //second row
            -1.0f, 0.33f, 0.0f,     1.0f, 1.0f, 1.0f,
            -0.33f, 0.33f, 0.0f,    1.0f, 1.0f, 1.0f,
            0.33f, 0.33f, 0.0f,     1.0f, 1.0f, 1.0f,
            1.0f, 0.33f, 0.0f,      1.0f, 1.0f, 1.0f,

            //third row
            -1.0f, -0.33f, 0.0f,    1.0f, 1.0f, 1.0f,
            -0.33f, -0.33f, 0.0f,   1.0f, 1.0f, 1.0f,
            0.33f, -0.33f, 0.0f,    1.0f, 1.0f, 1.0f,
            1.0f, -0.33f, 0.0f,     1.0f, 1.0f, 1.0f,

            //fourth row
            -1.0f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
            -0.33f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f,
            0.33f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,      1.0f, 1.0f, 1.0f,
    };

    float vertices_black[] = {
            //first row             //color
            -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, 0.0f,
            -0.33f, 1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
            0.33f, 1.0f, 0.0f,      0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f,       0.0f, 0.0f, 0.0f,

            //second row
            -1.0f, 0.33f, 0.0f,     0.0f, 0.0f, 0.0f,
            -0.33f, 0.33f, 0.0f,    0.0f, 0.0f, 0.0f,
            0.33f, 0.33f, 0.0f,     0.0f, 0.0f, 0.0f,
            1.0f, 0.33f, 0.0f,      0.0f, 0.0f, 0.0f,

            //third row
            -1.0f, -0.33f, 0.0f,    0.0f, 0.0f, 0.0f,
            -0.33f, -0.33f, 0.0f,   0.0f, 0.0f, 0.0f,
            0.33f, -0.33f, 0.0f,    0.0f, 0.0f, 0.0f,
            1.0f, -0.33f, 0.0f,     0.0f, 0.0f, 0.0f,

            //fourth row
            -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
            -0.33f, -1.0f, 0.0f,    0.0f, 0.0f, 0.0f,
            0.33f, -1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,      0.0f, 0.0f, 0.0f,
    };

    unsigned int elements[] = {  // note that we start from 0!
            0, 1, 5, 4, 65535,
            1, 2, 6, 5, 65535,
            2, 3, 7, 6, 65535,
            4, 5, 9, 8, 65535,
            5, 6, 10, 9, 65535,
            6, 7, 11, 10, 65535,
            8, 9, 13, 12, 65535,
            9, 10, 14, 13, 65535,
            10, 11, 15, 14,
    };

    float texCoords[] = {
            0.0f, 0.0f,  // lower-left corner
            1.0f, 0.0f,  // lower-right corner
            0.0f, 1.0f,  // top-left corner
            1.0f, 1.0f,  //top-right corner
    };


    //TODO figure out why glBufferSubData didn't work
    float color_white[] {
        1.0f, 1.0f, 1.0f
    };

    float color_black[] {
        0.0f, 0.0f, 0.0f
    };

    //top layer grid
    unsigned int VAO1, VBO1, EBO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO1);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_black), vertices_black, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(65535);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glBindVertexArray(0);

    //base layer squares (with textures?)
    unsigned int VAO2, VBO2, VBO2_tex, EBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &VBO2_tex);
    glGenBuffers(1, &EBO2);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_white), vertices_white, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //FIXME experimental
    // texture coord attribute
    /*glBindBuffer(GL_ARRAY_BUFFER, VBO2_tex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);*/

//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, VBO2);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(65535);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO2 as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    //FIXME experimental
    // load and create a texture
    // -------------------------
    /*unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);*/



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawMultiArrays() ???

        ourShader.use();

        glBindVertexArray(VAO2);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_white), vertices_white);
        glDrawElements(GL_TRIANGLE_FAN, 44, GL_UNSIGNED_INT, nullptr);


        glBindVertexArray(VAO1);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_black), vertices_black);
        glDrawElements(GL_LINE_LOOP, 44, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return EXIT_SUCCESS;
}
