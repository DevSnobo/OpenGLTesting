#include <utility>

//
// Created by snobo on 6/5/19.
//

#include "text.h"

Container::Container(GLfloat x, GLfloat y, glm::vec3 color, GLfloat width, GLfloat scale)
        : con_color(color), con_scale(scale) {
    this->con_x = x - 10;
    this->con_y = y - (FONT_SIZE / 2.0f * this->con_scale) + (8.0f * this->con_scale);
    this->con_width = width;
    this->con_height = (FONT_SIZE * this->con_scale) + (20.0f * this->con_scale);
}

Container::Container(glm::vec3 color, GLfloat width)
        : con_color(color), con_width(width) {
}

GLfloat Container::getWidth() {
    return this->con_width;
}

GLfloat Container::getHeight() {
    return this->con_height;
}

Text::Text(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
        : text_x(x), text_y(y), text_scale(scale), text_color(color), text_container(nullptr) {
    this->text = std::move(text);
}

Text::Text(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, Container *con)
        : text_x(x), text_y(y), text_scale(scale), text_color(color), text_container(con) {
    this->text = std::move(text);
    this->text_container = new Container(this->text_x, this->text_y, con->con_color, con->getWidth(), this->text_scale);
}

Text::Text(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, bool selected, Container *con)
        : text_x(x), text_y(y), text_scale(scale), text_color(color), text_container(con), text_is_selected(selected) {
    this->text = std::move(text);
    this->text_container = new Container(this->text_x, this->text_y, con->con_color, con->getWidth(), this->text_scale);
}

void Text::setText(std::string new_text) {
    this->text = std::move(new_text);
}

void Text::setSelected() {
    this->text_is_selected = true;
}

void Text::resetSelected() {
    this->text_is_selected = false;
}

