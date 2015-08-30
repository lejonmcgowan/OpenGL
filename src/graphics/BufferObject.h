//
// Created by lejonmcgowan on 7/11/15.
//

#ifndef TESTPROJECT2_BUFFEROBJECT_H
#define TESTPROJECT2_BUFFEROBJECT_H


#include <map>
#include <string>
#include <GL/glew.h>

#include "Buffer.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "math/Transform.h"

class BufferObject
{
private:
    Transform transform;
    std::map<std::string, Buffer*> buffers;
    std::map<std::string, Texture*> textures;
    GLuint vao;
    IndexBuffer indexBuffer;
    static int texIter;
    int attribIter = 0;
public:
    BufferObject(){};
    void addBuffer(std::string name, int blockSize);
    void addTexture(std::string name, std::string path);
    void addBufferVertexAttrib(std::string name,int size, int offset);

    Texture& getTexture(std::string name){return *textures[name];}
    Buffer& getBuffer(std::string name){return *buffers[name];}
    IndexBuffer& getIndexBuffer(){return indexBuffer;}
    GLuint getVAO(){return vao;}
    Transform& getTransform(){return transform;}

    void init();
    void bindVAO(){glBindVertexArray(vao);};
    void unbindVAO(){glBindVertexArray(0);};

    void bindTextures();

    void init(GLenum drawType);
};


#endif //TESTPROJECT2_BUFFEROBJECT_H
