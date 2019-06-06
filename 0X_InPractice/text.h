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

class Container {
public:
    GLfloat con_x;
    GLfloat con_y;
    GLfloat con_color;

    Container(GLfloat x, GLfloat y, GLfloat color);
    Container(GLfloat x, GLfloat y, GLfloat color, GLfloat width, GLfloat height);
    Container() = default;
    ~Container() = default;
    void setWidth(GLfloat width);
    void setHeight(GLfloat height);

private:
    GLfloat con_width;
    GLfloat con_height;
};

class Text {
public:
    std::string name;
    std::string text;
    GLfloat text_x{};
    GLfloat text_y{};
    GLfloat text_scale{};
    glm::vec3 text_color{};
    Container *text_container;

    Text(std::string name, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    Text();
    ~Text() = default;
    void addContainer(Container con);
};

#endif //TEXT_H
