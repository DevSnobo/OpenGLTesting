#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <iostream>

#include "texture.h"
#include "shader.h"
#include "text.h"

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

class TextRenderer
{
public:
    TextRenderer(Shader &shader);
    // Destructor
    ~TextRenderer();

    void DrawText(Text &text);

private:
    Shader shader;
    std::map<GLchar, Character> Characters;

    void initCharacters();
    void Init();
};



#endif //TEXT_RENDERER_H
