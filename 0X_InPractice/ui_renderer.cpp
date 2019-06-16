//
// Created by snobo on 6/9/19.
//

#include <iostream>
#include "ui_renderer.h"

#define MENU_HIGHLIGHT_DEFAULT 0.2f
#define MENU_HIGHLIGHT_SELECTED 0.4f

GLuint text_VAO, text_VBO, quad_VAO, quad_VBO;

UiRenderer::UiRenderer(Shader *box_shader, Shader *text_shader) {
    this->box_shader = box_shader;
    this->text_shader = text_shader;
    this->Characters = std::map<GLchar, Character>();
    Init();
    initCharacters();
}

void UiRenderer::DrawBoxes(Ui *ui, GameState state) {
    if (state == GAME_MENU) {
        for (std::pair<std::string, Text *> pair : Ui::Menus.at(ui->getMenuState()).second.Texts) {
            DrawBox(pair.second);
        }
    }
}

void UiRenderer::DrawTexts(Ui *ui, GameState state) {
    if (state == GAME_ACTIVE) {
        for (std::pair<std::string, Text *> pair : Ui::Menus.at(ui->getMenuState()).second.Texts) {
            DrawText(pair.second);
        }
    } else if (state == GAME_MENU) {
        for (std::pair<std::string, Text *> pair : Ui::Menus.at(ui->getMenuState()).second.Texts) {
            DrawText(pair.second);
        }
    }
}

void UiRenderer::DrawText(Text *t) {
    text_shader->Use();
    glUniform3f(glGetUniformLocation(text_shader->ID, "textColor"), t->text_color.x, t->text_color.y, t->text_color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    GLfloat tmp = t->text_x;
    for (c = t->text.begin(); c != t->text.end(); c++) {
        Character ch = this->Characters[*c];

        GLfloat xpos = t->text_x + ch.Bearing.x * t->text_scale;
        GLfloat ypos = t->text_y - (ch.Size.y - ch.Bearing.y) * t->text_scale;

        GLfloat w = ch.Size.x * t->text_scale;
        GLfloat h = ch.Size.y * t->text_scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos + h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        t->text_x += (ch.Advance >> 6) * t->text_scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    t->text_x = tmp;
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void UiRenderer::DrawBox(Text *t) {
    //auto *con = t->text_container;

    if (t->text_container == nullptr) {
        return;
    }
    //TODO: shader stuff to draw rectangle + filled rectangles
    box_shader->Use();

    GLfloat alpha;
    glm::vec3 color = t->text_container->con_color;
    if (t->text_is_selected) {
        alpha = MENU_HIGHLIGHT_SELECTED;
        //color = color;
    } else {
        alpha = MENU_HIGHLIGHT_DEFAULT;
    }

    glUniform4f(glGetUniformLocation(box_shader->ID, "quad_color"), color.y, color.y, color.z, alpha);
    glBindVertexArray(quad_VAO);

    GLfloat vertices[6][2] = {
            {t->text_container->con_x,
                t->text_container->con_y + t->text_container->getHeight()},
            {t->text_container->con_x,
                t->text_container->con_y},
            {t->text_container->con_x + t->text_container->getWidth(),
                t->text_container->con_y},

            {t->text_container->con_x + t->text_container->getWidth(),
                t->text_container->con_y},
            {t->text_container->con_x + t->text_container->getWidth(),
                t->text_container->con_y + t->text_container->getHeight()},
            {t->text_container->con_x,
                t->text_container->con_y + t->text_container->getHeight()}
    };

    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, quad_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void UiRenderer::Init() {
    //text stuff
    glGenVertexArrays(1, &text_VAO);
    glGenBuffers(1, &text_VBO);
    glBindVertexArray(text_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //box stuff
    glGenVertexArrays(1, &quad_VAO);
    glGenBuffers(1, &quad_VBO);
    glBindVertexArray(quad_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, quad_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 2, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//IMPROVE: support special characters like Ä Ö Ü ß
void UiRenderer::initCharacters() {
    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";
    }

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, "/usr/share/fonts/TTF/arial.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font\n";
    }

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, FONT_SIZE);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph\n";
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
        };
        this->Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
