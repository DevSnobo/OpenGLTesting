//
// Created by snobo on 6/6/19.
//

#include "text.h"
#include "menu.h"

void Menu::addText(const std::string& name, Text *text) {
    Texts.emplace(std::pair<std::string, Text*>(name, text));
}