#include <utility>

#include <utility>

//
// Created by snobo on 6/6/19.
//

#ifndef MENU_H
#define MENU_H

#include <cstdarg>
#include <vector>
#include <map>
#include <string>
#include "text.h"

//template <typename T = std::string, typename...U>
//using Enable = void;
class Menu {
public:
    std::map<std::string, Text*> Texts;
    std::string menu_title;

    /*template <typename T = std::string, typename... U>
    Menu(const T& title, U&... t) : Menu(t...) {
        *//*if (std::is_same<std::string, T>::value) {
            menu_title = title;
        }*//*
//        Texts.emplace_back(&t...);
//        temp = {t...};
    }*/

    //FIXME //REVIEW
    //TODO: fix constructor to accept multiple Text objects
    template <typename T = std::string>
    Menu(std::string title) {
        menu_title = std::move(title);
        Texts = std::map<std::string, Text*>();
    }

    /*template <typename U>
    Menu(U t) {
        if (std::is_same<Text, U>::value) {
            Texts.insert(t);
        }
    }*/

    ~Menu() = default;

    void addText(const std::string& name, Text *text);
};

#endif //MENU_H
