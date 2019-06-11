//
// Created by snobo on 6/9/19.
//

#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "shader.h"
#include "ui.h"
#include "game.h"

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

class UiRenderer {
public:
    UiRenderer(Shader *box_shader, Shader *text_shader);
    ~UiRenderer() = default;

    void DrawBoxes(Ui *ui, GameState state);
    void DrawTexts(Ui *ui, GameState state);

private:
    Shader *box_shader;
    Shader *text_shader;
    std::map<GLchar, Character> Characters;

    void DrawText(Text *t);
    void DrawBox(Text *t);
    void Init();
    void initCharacters();
};

#endif //UI_RENDERER_H
