//
// Created by snobo on 6/8/19.
//

#ifndef UI_H
#define UI_H

#include <glad/glad.h>
#include <unordered_map>
#include <ft2build.h>
#include <vector>
#include FT_FREETYPE_H

#include "shader.h"
#include "menu.h"
#include "text.h"

enum MenuState {
    MENU_NONE = 0,
    MENU_MAIN = 1,
    MENU_SETTINGS = 2
};

class Ui {
public:
    static std::vector<std::pair<MenuState, Menu>> Menus;

    Ui(GLuint lives, GLuint blocks);
    ~Ui();

    void setLives(GLuint change);
    void decreaseBlocksRemaining();
    void increasePaddleBounces();
    void updateLives();
    void updateBlocks();
    void updateBounces();

    MenuState getMenuState();
    void setMenuState(MenuState state);

private:
    GLuint lives;
    GLuint blocks_remaining;
    GLuint paddle_bounces;
    MenuState state = MENU_NONE;
};

#endif //UI_H
