//
// Created by snobo on 6/6/19.
//

#include "renderer.h"

Renderer::Renderer() {
    sprite_renderer = nullptr;
    ui_renderer = nullptr;
    text_renderer = nullptr;
}

Renderer::~Renderer() {
    delete sprite_renderer;
    delete ui_renderer;
    delete text_renderer;
}

void Renderer::Init() {
    sprite_shader = ResourceManager::GetShader("sprite");
    sprite_renderer = new SpriteRenderer(&sprite_shader);

    box_shader = ResourceManager::GetShader("box");
    text_shader = ResourceManager::GetShader("text");
    ui_renderer = new UiRenderer(&box_shader, &text_shader);

    text_renderer = new TextRenderer(&text_shader);
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
    // Menu texts
    ResourceManager::LoadText("menu_title", "Menu", 320.0f, 500.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    ResourceManager::LoadText("menu_option_1", "Resume", 220.0f, 400.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

    // Game End texts
    ResourceManager::LoadText("game_end_win", "YOU WON!", 200.0f, 350.0f, 1.25f, glm::vec3(1.0f, 1.0f, 1.0f));
    ResourceManager::LoadText("game_end_lose", "GAME OVER!", 160.0f, 350.0f, 1.25f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Renderer::LoadUi(Ui *ui) {
    //IMPROVE: load texts with all properties from file
    Menu *none = new Menu("menu_none");
    none->addText("game_count_lives", new Text("lives: ___", 15.0f, 55.0f, 0.4f, glm::vec3(1.0f)));
    none->addText("game_count_remaining", new Text("remaining: ___", 15.0f, 575.0f, 0.4f, glm::vec3(1.0f)));
    none->addText("game_count_bounce", new Text("bounces: ___", 630.0f, 55.0f, 0.4f, glm::vec3(1.0f)));
    Ui::Menus.emplace(std::pair<MenuState, Menu>(MENU_NONE, *none));
    Menu *main_menu = new Menu(
            "menu_main"/*,
            Text("menu_main_title", "Main Menu", 320.0f, 500.0f, 1.0f, glm::vec3(1.0f)),
            Text("menu_main_resume", "Resume", 220.0f, 400.0f, 0.5f, glm::vec3(1.0f)),
            Text("menu_main_resume", "Resume", 220.0f, 400.0f, 0.5f, glm::vec3(1.0f)),
            Text("menu_main_resume", "Resume", 220.0f, 400.0f, 0.5f, glm::vec3(1.0f))*/);

    main_menu->addText("menu_main_title", new Text("Main Menu", 220.0f, 500.0f, 1.0f, glm::vec3(1.0f)));
    main_menu->addText("menu_main_resume", new Text("Resume", 220.0f, 400.0f, 0.5f, glm::vec3(1.0f)));
    Ui::Menus.emplace(std::pair<MenuState, Menu>(MENU_MAIN, *main_menu));
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

void Renderer::Draw(Texture2D &texture, glm::vec2 start, glm::vec2 end, GLfloat rotate) {
    sprite_renderer->DrawSprite(texture, start, end, rotate);
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

void Renderer::Draw(Ui *ui, GameState state) {
    switch (state) {
        case GAME_ACTIVE:
            ui_renderer->DrawTexts(ui, state);
            break;
        case GAME_MENU:
            ui_renderer->DrawBoxes(ui, state);
            ui_renderer->DrawTexts(ui, state);
            break;

        case GAME_WIN:
            //TODO: define win screen
            break;

        default:
            puts("something went wrong, unknown gamestate");
    }
}

GameState Renderer::getGameState() {
    return this->game_state;
}

void Renderer::setGameState(GameState state) {
    this->game_state = state;
}


