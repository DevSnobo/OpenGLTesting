//
// Created by snobo on 1/15/19.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


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


    //TODO figure out why glBufferSubData didn't work
    float color_white[] {
        1.0f, 1.0f, 1.0f
    };

    float color_black[] {
        0.0f, 0.0f, 0.0f
    };

    /* unsigned int indices1[] = {  // note that we start from 0!
             //sq1
             0, 1, 5, 4,
     };
     unsigned int indices2[] = {
             //sq2
             1, 2, 6, 5,};
     unsigned int indices3[] = {
             //sq3
             2, 3, 7, 6,};
     unsigned int indices4[] = {
             //sq4
             4, 5, 9, 8,};
     unsigned int indices5[] = {
             //sq5
             5, 6, 10, 9,};
     unsigned int indices6[] = {
             //sq6
             6, 7, 11, 10,};
     unsigned int indices7[] = {
             //sq7
             8, 9, 13, 12,};
     unsigned int indices8[] = {
             //sq8
             9, 10, 14, 13,};
     unsigned int indices9[] = {
             //sq9
             10, 11, 15, 14,};*/

    unsigned int VBO, VAO, EBO; //, EBO1, EBO2, EBO3, EBO4, EBO5, EBO6, EBO7, EBO8, EBO9;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    /*glGenBuffers(1, &EBO1);
    glGenBuffers(1, &EBO2);
    glGenBuffers(1, &EBO3);
    glGenBuffers(1, &EBO4);
    glGenBuffers(1, &EBO5);
    glGenBuffers(1, &EBO6);
    glGenBuffers(1, &EBO7);
    glGenBuffers(1, &EBO8);
    glGenBuffers(1, &EBO9);*/
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_white), vertices_white, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(65535);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    /*  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices5), indices5, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices6), indices6, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices7), indices7, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices8), indices8, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices9), indices9, GL_STATIC_DRAW);*/


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

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

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_white), vertices_white);
        glDrawElements(GL_TRIANGLE_FAN, 44, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_black), vertices_black);
        glDrawElements(GL_LINE_LOOP, 44, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return EXIT_SUCCESS;
}
