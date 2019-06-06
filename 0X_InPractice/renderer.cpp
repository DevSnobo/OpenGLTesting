//
// Created by snobo on 6/6/19.
//

#include "renderer.h"


Renderer::Renderer() {
    sprite_renderer = nullptr;
    text_renderer = nullptr;
}

Renderer::~Renderer() {
    delete sprite_renderer;
    delete text_renderer;
}

void Renderer::Init() {
    sprite_shader = ResourceManager::GetShader("sprite");

    std::cout << "instantiating sprite renderer\n";
    sprite_renderer = new SpriteRenderer(sprite_shader);
    std::cout << "sprite renderer instantiated\n";

    text_shader = ResourceManager::GetShader("text");
    text_renderer = new TextRenderer(text_shader);
}

void Renderer::LoadShaders() {
    // Load shaders
    ResourceManager::LoadShader("../0X_InPractice/shaders/sprite.vs",
                                "../0X_InPractice/shaders/sprite.fs", nullptr, "sprite");
    ResourceManager::LoadShader("../0X_InPractice/shaders/text.vs",
                                "../0X_InPractice/shaders/text.fs", nullptr, "text");
}

void Renderer::LoadTextures() {
    // Load textures
    ResourceManager::LoadTexture("../0X_InPractice/textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("../0X_InPractice/textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("../0X_InPractice/textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("../0X_InPractice/textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("../0X_InPractice/textures/paddle.png", true, "paddle");
}

void Renderer::LoadTexts() {
    // Load texts
    ResourceManager::LoadText("menu_title", "Menu", 320.0f, 500.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    ResourceManager::LoadText("menu_option_1", "Test Option 1", 320.0f, 400.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Renderer::LoadLevels(Game *game) {
    // Load levels
    GameLevel one, two, three, four;
    one.Load("../0X_InPractice/levels/01.lvl", game->Width, game->Height * 0.5);
    two.Load("../0X_InPractice/levels/02.lvl", game->Width, game->Height * 0.5);
    three.Load("../0X_InPractice/levels/03.lvl", game->Width, game->Height * 0.5);
    four.Load("../0X_InPractice/levels/04.lvl", game->Width, game->Height * 0.5);
    game->Levels.push_back(one);
    game->Levels.push_back(two);
    game->Levels.push_back(three);
    game->Levels.push_back(four);
    game->Level = 0;
}

void Renderer::PushUniforms(Game *game) {
    // sprite stuff
    glm::mat4 sprite_projection = glm::ortho(0.0f, static_cast<GLfloat>(game->Width), //
                                             static_cast<GLfloat>(game->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", sprite_projection);
    // text stuff
    glm::mat4 text_projection = glm::ortho(0.0f, static_cast<GLfloat>(game->Width), //
                                           0.0f, static_cast<GLfloat>(game->Height));
    ResourceManager::GetShader("text").Use().SetInteger("text", 0);
    ResourceManager::GetShader("text").SetMatrix4("projection", text_projection);
}

void Renderer::Draw(Texture2D texture, glm::vec2 start, glm::vec2 end, GLfloat alpha) {
    sprite_renderer->DrawSprite(texture, start, end, alpha);
}

void Renderer::Draw(Text text) {
    text_renderer->DrawText(text);
}

void Renderer::Draw(GameObject *object) {
    sprite_renderer->DrawSprite(object->Sprite, object->Position, object->Size, object->Rotation, object->Color);
}

void Renderer::Draw(GameLevel *level) {
    for (GameObject &tile : level->Bricks) {
        if (!tile.Destroyed) {
            sprite_renderer->DrawSprite(tile.Sprite, tile.Position, tile.Size, tile.Rotation, tile.Color);
        }
    }
}

