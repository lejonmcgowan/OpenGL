//
// Created by lejonmcgowan on 7/11/15.
//

#include <assert.h>
#include "Texture.h"
#include "debugGL.h"

void Texture::init()
{
    assert(texNum > -1);

    glGenTextures(1, &handle);
    glBindTexture(type, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load, create texture and generate mipmaps
    image = SOIL_load_image(path.c_str(), &width, &height, 0, SOILLoadType);
    glTexImage2D(type, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, image);

    if(enableMipMap)
        glGenerateMipmap(type);

    SOIL_free_image_data(image);
    glBindTexture(type, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
    assert(checkGLError);
}