#pragma once

#include <GL\glew.h>

#include "renderer/stb_image.h"

class Texture
{
public:
    Texture();
    Texture(const char* fileLoc);

    bool LoadTexture();
    bool LoadTextureA();
    bool LoadTextureMem(int pWidth, int pHeight);
    void updateImage(unsigned char* pData, int pWidth, int pHeight);

    void UseTexture();
    void ClearTexture();

    ~Texture();

    int getWidth() const;
    int getHeight() const;

private:
    GLuint textureID;
    int width, height, bitDepth;

    const char* fileLocation;

    unsigned char *mMemData = nullptr;
};

