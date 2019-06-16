//
// Created by snobo on 6/6/19.
//
#ifndef MENU_H

#define MENU_H

#include <vector>
#include <string>
#include "text.h"

class Menu {
public:
    std::vector<std::pair<std::string, Text*>> Texts;
    std::string menu_title;

    template <typename S, typename... T>
    Menu(const S& title, T ...t) : menu_title(title), Texts({t...}){
    }

    Menu() = default;
    ~Menu() = default;
};

#endif //MENU_H
