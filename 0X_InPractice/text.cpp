#include <utility>

//
// Created by snobo on 6/5/19.
//

#include "text.h"

Container::Container(GLfloat x, GLfloat y, GLfloat color)
        : con_x(x), con_y(y), con_color(color), con_width(0), con_height(0) {}

Container::Container(GLfloat x, GLfloat y, GLfloat color, GLfloat width, GLfloat height)
        : con_x(x), con_y(y), con_color(color) {
    this->con_width = width;
    this->con_height = height;
}

void Container::setWidth(GLfloat width) {
    this->con_width = width;
}

void Container::setHeight(GLfloat height) {
    this->con_height = height;
}

Text::Text(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
        : text_x(x), text_y(y), text_scale(scale), text_color(color), text_container(nullptr) {
    this->text = std::move(text);
}

void Text::addContainer(Container con) {
    text_container = &con;

    if (text_container != nullptr) {
        //CATEGORY: Menu
        //TODO: calculate container bounds
        text_container->setWidth(150.0f);
        text_container->setHeight(50.0f);
    }
}

void Text::setText(std::string new_text) {
    this->text = std::move(new_text);
}

Text::Text() = default;

