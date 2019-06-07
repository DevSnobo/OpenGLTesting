

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include "renderer.h"

// Game-related State data
Renderer *renderer;
GameObject *Player;
BallObject *Ball;

Game::Game(GLuint width, GLuint height)
        : State(GAME_ACTIVE), Keys(), Width(width), Height(height), Levels(), Level(0) {
    renderer = new Renderer();
}

Game::~Game() {
    delete renderer;
    delete Player;
    delete Ball;
}

void Game::Init() {
    renderer->LoadShaders();
    renderer->PushUniforms(this);
    renderer->LoadTextures();
    renderer->LoadTexts();
    renderer->LoadLevels(this);
    renderer->Init();

    // Configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}

void Game::Update(GLfloat dt) {
    if (this->State == GAME_ACTIVE) {
        // Update objects
        Ball->Move(dt, this->Width);
        // Check for collisions
        this->DoCollisions();

        if (Ball->Position.y >= this->Height) // Did ball reach bottom edge?
        {
            this->ResetLevel();
            this->ResetPlayer();
        }
        if (this->Levels[this->Level].IsCompleted()) {
            if (this->Level < this->Levels.size() - 1) {
                this->Level += 1;
            } else {
                //TODO: handle end of game
            }
            this->ResetPlayer();
            Ball->Stuck = true;
        }
    } else if (this->State == GAME_MENU) {
    }
}

void Game::ProcessInput(GLfloat dt) {
    if (this->State == GAME_ACTIVE) {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_LEFT]) {
            if (Player->Position.x >= 0) {
                Player->Position.x -= velocity;
                if (Ball->Stuck) {
                    Ball->Position.x -= velocity;
                }
            }
        }
        if (this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT]) {
            if (Player->Position.x <= this->Width - Player->Size.x) {
                Player->Position.x += velocity;
                if (Ball->Stuck) {
                    Ball->Position.x += velocity;
                }
            }
        }
        if (this->Keys[GLFW_KEY_SPACE]) {
            Ball->Stuck = false;
        }
    } else if (this->State == GAME_MENU) {
        //TODO: menu handling
    }
}

void Game::Render() {
    if (this->State == GAME_ACTIVE) {
        // Draw background
        Texture2D background = ResourceManager::GetTexture("background");
        renderer->Draw(background, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);

        renderer->Draw(&this->Levels[this->Level]);
        renderer->Draw(Player);
        renderer->Draw(Ball);
    }
    if (this->State == GAME_MENU) {
        Texture2D background = ResourceManager::GetTexture("background");
        renderer->Draw(background, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);

        Text text;
        text = ResourceManager::GetText("menu_title");
        renderer->Draw(text);
        text = ResourceManager::GetText("menu_option_1");
        renderer->Draw(text);
        //TODO: create menu + handling
    }
    if (this->State == GAME_WIN) {
        //TODO: handle end of game / inbetween levels?
    }
}

void Game::ResetLevel() {
    renderer->LoadLevels(this);
}

void Game::ResetPlayer() {
    // Reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)),
                INITIAL_BALL_VELOCITY);
    Ball->Stuck = GL_TRUE;
}

// Collision detection
Collision CheckCollision(BallObject &one, GameObject &two);

Direction VectorDirection(glm::vec2 target);

void Game::DoCollisions() {
    for (GameObject &box : this->Levels[this->Level].Bricks) {
        if (!box.Destroyed) {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision)) // If collision is true
            {
                // Destroy block if not solid
                if (!box.IsSolid) {
                    box.Destroyed = GL_TRUE;
                }
                // Collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) // Horizontal collision
                {
                    Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT) {
                        Ball->Position.x += penetration; // Move ball to right
                    } else {
                        Ball->Position.x -= penetration;
                    } // Move ball to left;
                } else // Vertical collision
                {
                    Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP) {
                        Ball->Position.y -= penetration; // Move ball back up
                    } else {
                        Ball->Position.y += penetration;
                    } // Move ball back down
                }
            }
        }
    }

    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->Stuck && std::get<0>(result)) {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size.x / 2);
        // Then move accordingly
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
    }
}

Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // Get center point circle first
    glm::vec2 center(one.Position + one.Radius);
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
    // Get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // Now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;

    if (glm::length(difference) <
        one.Radius) { // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
    } else {
        return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
    }
}

// Calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target) {
    glm::vec2 compass[] = {
            glm::vec2(0.0f, 1.0f),    // up
            glm::vec2(1.0f, 0.0f),    // right
            glm::vec2(0.0f, -1.0f),    // down
            glm::vec2(-1.0f, 0.0f)    // left
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++) {
        GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max) {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction) best_match;
}
