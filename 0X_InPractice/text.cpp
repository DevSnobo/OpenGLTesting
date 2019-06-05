#include <utility>

//
// Created by snobo on 6/5/19.
//

#include "text.h"

Text::Text(std::string name, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
        : x_pos(x), y_pos(y), scale(scale), color(color) {
    this->name = std::move(name);
    this->text = std::move(text);
}

Text::Text() = default;

