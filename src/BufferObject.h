//
// Created by lejonmcgowan on 7/11/15.
//

#ifndef TESTPROJECT2_BUFFEROBJECT_H
#define TESTPROJECT2_BUFFEROBJECT_H


#include "Buffer.h"
#include "Texture.h"
#include "IndexBuffer.h"

#include <map>
#include <string>
#include <GL/glew.h>

class BufferObject
{
private:
    std::map<std::string, Buffer> buffers;
    std::map<std::string, Texture> textures;
    GLuint vao;
    IndexBuffer indexBuffer;
    int textIter = 0, attribIter = 0;
public:
    BufferObject();
    void addBuffer(std::string name,GLuint type);
    void addBufferVertexAttrib(std::string name,int size, int numFloatsPerElement, int offset);
    void addTexture(std::string name);
    int getTextureIndex(std::string name);
    GLuint getTextureHandle(std::string name);
    GLuint getVAO(){return vao;}

    void init();
    void bind(){glBindVertexArray(vao);};
    void unbind(){glBindVertexArray(0);};
};


#endif //TESTPROJECT2_BUFFEROBJECT_H
