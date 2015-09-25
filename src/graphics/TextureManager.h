//
// Created by lejonmcgowan on 9/18/15.
//

#ifndef TESTPROJECT2_TEXTUREMANAGER_H
#define TESTPROJECT2_TEXTUREMANAGER_H


#include "Texture.h"
#include <vector>
#include <assert.h>
#include <map>
#include <iostream>

class TextureManager
{
private:
    const static int size = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
    static std::map<std::string,Texture *> textures;
    static bool* availableIndeces; //true means the index is occupied

    static int getNextIndex()
    {
        int i = -1;
        while(availableIndeces[++i]);
        std::cout << i << std::endl;
        assert(i < size);
        availableIndeces[i] = true;
        return i;
    }

    static bool* makeArray()
    {
        bool* indices = new bool[size]();
        indices[0] = true;
        return indices;
    }

public:
    static void addTexture(std::string name, std::string imagePath);
    static void removeTexture(std::string name);
    static int getTexIndex(std::string name);
    static void clearTextures();
    static void bindTextures();
    static void unbindTextures();
    static void init();
};


#endif //TESTPROJECT2_TEXTUREMANAGER_H
