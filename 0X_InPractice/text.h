//
// Created by snobo on 6/5/19.
//

#ifndef TEXT_H
#define TEXT_H

#include <glad/glad.h>
#include <string>

#ifndef SHADER_H
#define SHADER_H
#include "../glm/glm.hpp"
#endif

class Text
{
public:
    Text(std::string name, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    Text();
    ~Text() = default;

    std::string name;
    std::string text;
    GLfloat x_pos{};
    GLfloat y_pos{};
    GLfloat scale{};
    glm::vec3 color{};
};

#endif //TEXT_H
