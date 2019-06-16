//
// Created by snobo on 6/6/19.
//

#include "text.h"
#include "menu.h"

void Menu::addText(const std::pair<std::string, Text *>& in_pair) {
    std::vector<std::pair<std::string, Text*>>::const_iterator it;
    bool changed = false;

    for (it = Texts.begin(); it != Texts.end(); it++) {
        if (it->first == in_pair.first) {
            Texts.erase(it);
            Texts.insert(it, in_pair);
            changed = true;
            break;
        }
    }

    if (!changed) {
        Texts.insert(Texts.end(), in_pair);
    }

}