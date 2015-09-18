//
// Created by lejonmcgowan on 7/11/15.
//

#ifndef TESTPROJECT2_BUFFEROBJECT_H
#define TESTPROJECT2_BUFFEROBJECT_H


#include <map>
#include <string>
#include <GL/glew.h>

#include "graphics/Buffer.h"
#include "graphics/Texture.h"
#include "graphics/IndexBuffer.h"
#include "math/Transform.h"

class BufferObject
{
private:
    Transform transform;
    std::map<std::string, Buffer*> buffers;
    GLuint vao;
    IndexBuffer indexBuffer;
public:
    BufferObject(){};
    void addBuffer(std::string name, int blockSize);
    void addBufferVertexAttrib(std::string name,int size, int offset, int index);

    Buffer& getBuffer(std::string name){return *buffers[name];}
    IndexBuffer& getIndexBuffer(){return indexBuffer;}
    GLuint getVAO(){return vao;}
    Transform& getTransform(){return transform;}

    void bindVAO(){glBindVertexArray(vao);};
    void unbindVAO(){glBindVertexArray(0);};

    void init(GLenum drawType = GL_STATIC_DRAW);
    void render(GLenum drawType, int numVertices);
};


#endif //TESTPROJECT2_BUFFEROBJECT_H
