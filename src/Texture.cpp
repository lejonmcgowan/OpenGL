//
// Created by lejonmcgowan on 7/11/15.
//

#include <assert.h>
#include "Texture.h"

void Texture::init()
{
    assert(texNum > -1);

    glGenTextures(1, &handle);
    glBindTexture(type, handle);

    // Load, create texture and generate mipmaps
    image = SOIL_load_image(path.c_str(), &width, &height, 0, SOILLoadType);
    glTexImage2D(type, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, image);

    if(enableMipMap)
        glGenerateMipmap(type);
    SOIL_free_image_data(image);
    glBindTexture(type, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}