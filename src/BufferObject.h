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
    std::map<std::string, Buffer*> buffers;
    std::map<std::string, Texture*> textures;
    GLuint vao;
    IndexBuffer indexBuffer;
    int texIter = 0, attribIter = 0;
public:
    BufferObject(){};
    void addBuffer(std::string name, int blockSize);
    void addTexture(std::string name, std::string path);
    void addBufferVertexAttrib(std::string name,int size, int offset);
    Texture& getTexture(std::string name){return *textures[name];}
    Buffer& getBuffer(std::string name){return *buffers[name];}
    IndexBuffer& getIndexBuffer(){return indexBuffer;}
    GLuint getVAO(){return vao;}

    void init();
    void bind(){glBindVertexArray(vao);};
    void unbind(){glBindVertexArray(0);};


    void init(GLenum drawType);
};


#endif //TESTPROJECT2_BUFFEROBJECT_H
