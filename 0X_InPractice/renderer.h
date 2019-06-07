//
// Created by snobo on 6/6/19.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"
#include "game.h"

class Renderer {
public:
    SpriteRenderer *sprite_renderer;
    TextRenderer *text_renderer;
    Shader sprite_shader;
    Shader text_shader;

    Renderer();
    ~Renderer();
    void Init();
    void LoadShaders();
    void LoadTextures();
    void LoadTexts();
    void LoadLevels(Game *game);
    void PushUniforms(Game *game);
    void Draw(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate);
    void Draw(Text text);
    void Draw(GameObject *object);
    void Draw(GameLevel *level);
};

#endif //RENDERER_H
