//
// Created by lejonmcgowan on 7/11/15.
//

#ifndef TESTPROJECT2_TEXTURE_H
#define TESTPROJECT2_TEXTURE_H


#include <GL/glew.h>
#include <string>
#include "include/SOIL.h"

class Texture
{
private:
    int width,height;
    std::string path;
    GLuint handle;
    int texNum = -1;

    GLenum type = GL_TEXTURE_2D;
    GLint internalFormat = GL_RGB;
    bool enableMipMap = true;
    int SOILLoadType = SOIL_LOAD_RGB;

    unsigned char* image;
public:
    Texture(){}
    Texture(std::string path, int texNum):path(path),texNum(texNum){};
    GLuint& getHandle(){return handle;}
    int getTexIndex(){return texNum;}

    void setTexParam(GLenum  pname, GLfloat param){glTexParameterf(type,pname,param);}
    void setTexParam(GLenum  pname, GLint param){glTexParameteri(type,pname,param);}
    void setInternalFormat(GLint format){internalFormat = format;}
    void setTextureType(GLenum textureType){type = textureType;}

    void init();

    void bind();

    ~Texture(){glDeleteTextures(1,&handle);}
};


#endif //TESTPROJECT2_TEXTURE_H