//
// Created by snobo on 6/5/19.
//

#ifndef TEXT_H
#define TEXT_H
#define FONT_SIZE 60.0f

#include <glad/glad.h>
#include <string>

#ifndef SHADER_H
#define SHADER_H

#include "../glm/glm.hpp"

#endif

class Container {
public:
    GLfloat con_x{};
    GLfloat con_y{};
    glm::vec3 con_color;
    GLfloat con_scale{};

    Container(GLfloat x, GLfloat y, glm::vec3 color, GLfloat width, GLfloat scale);
    Container(glm::vec3 color, GLfloat width);
    ~Container() = default;

    GLfloat getWidth();
    GLfloat getHeight();

private:
    GLfloat con_width;
    GLfloat con_height{};
};

class Text {
public:
    std::string name;
    std::string text;
    GLfloat text_x{};
    GLfloat text_y{};
    GLfloat text_scale{};
    glm::vec3 text_color{};
    Container *text_container = nullptr;
    bool text_is_selected = false;

    Text() = default;
    Text(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    Text(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, Container *con);
    Text(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, bool selected, Container *con);
    ~Text() = default;

    void setText(std::string new_text);
    void setSelected();
    void resetSelected();
};

#endif //TEXT_H
