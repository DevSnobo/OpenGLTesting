

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"
#include "text.h"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager {
public:
    // Resource storage
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, Text> Texts;

    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
    // If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile,
                             const std::string &name);

    // Retrieves a stored shader
    static Shader& GetShader(const std::string &name);

    // Loads (and generates) a texture from file
    static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, const std::string &name);

    // Retrieves a stored texture
    static Texture2D GetTexture(const std::string &name);

    static Text
    LoadText(const std::string &name, const std::string &text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

    static Text GetText(const std::string &name);

    // Properly de-allocates all loaded resources
    static void Clear();

private:
    // Private constructor, that is we do not want any actual resource manager objects.
    // Its members and functions should be publicly available (static).
    ResourceManager() = default;

    // Loads and generates a shader from file
    static Shader
    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

    // Loads a single texture from file
    static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif

