//
// Created by snobo on 6/8/19.
//

#include <iostream>
#include "ui.h"

std::map<MenuState, Menu> Ui::Menus;
std::vector<Text *> Ui::Texts;

Ui::Ui(GLuint lives, GLuint blocks)
        : lives(lives), blocks_remaining(blocks), paddle_bounces(0) {
    puts("Ui constructor");
}

Ui::~Ui() {}

void Ui::setLives(GLuint new_lives) {
    this->lives = new_lives;
}

void Ui::decreaseBlocksRemaining() {
    this->blocks_remaining--;
}

void Ui::increasePaddleBounces() {
    this->paddle_bounces++;
}

void Ui::updateLives() {
    std::string new_lives = "lives: " + std::to_string(this->lives);

    for (std::pair<std::string, Text *> pair : Ui::Menus.at(getMenuState()).Texts) {
        if (pair.first == "game_count_lives") {
            pair.second->setText(new_lives);
        }
    }
}

void Ui::updateBlocks() {
    std::string new_blocks = "remaining: " + std::to_string(this->blocks_remaining);

    for (std::pair<std::string, Text *> pair : Ui::Menus.at(getMenuState()).Texts) {
        if (pair.first == "game_count_remaining") {
            pair.second->setText(new_blocks);
        }
    }
}

void Ui::updateBounces() {
    std::string new_bounces = "bounces: " + std::to_string(this->paddle_bounces);

    for (std::pair<std::string, Text *> pair : Ui::Menus.at(getMenuState()).Texts) {
        if (pair.first == "game_count_bounce") {
            pair.second->setText(new_bounces);
        }
    }
}

MenuState Ui::getMenuState() {
    return this->state;
}

void Ui::setMenuState(MenuState new_state) {
    this->state = new_state;
}

