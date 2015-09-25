//
// Created by lejonmcgowan on 9/18/15.
//

#include "TextureManager.h"

std::map<std::string,Texture> TextureManager::textures;
bool* TextureManager::availableIndeces = TextureManager::makeArray();

void TextureManager::addTexture(std::string name, std::string imagePath)
{
    textures.emplace(name,Texture(imagePath, getNextIndex()));
}

void TextureManager::removeTexture(std::string name)
{
    availableIndeces[textures[name].getTexIndex()] = false;
    textures.erase(name);
}

void TextureManager::clearTextures()
{
    textures.clear();
    delete[] availableIndeces;
    availableIndeces = makeArray();
}

void TextureManager::bindTextures()
{
    for(auto texture: textures)
        texture.second.bind();
}

void TextureManager::unbindTextures()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

int TextureManager::getTexIndex(std::string name)
{
    return textures[name].getTexIndex();
}

void TextureManager::init()
{
    for(auto texture: textures)
        texture.second.init();
}
