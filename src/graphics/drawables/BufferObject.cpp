//
// Created by lejonmcgowan on 7/11/15.
//

#include <iostream>
#include "BufferObject.h"
#include "utils/debugGL.h"

int BufferObject::texIter = 0;

void BufferObject::addBuffer(std::string name, int blockSize)
{
    buffers.emplace(name,new Buffer(blockSize));
}

void BufferObject::addTexture(std::string name, std::string path)
{
    textures.emplace(name,new Texture(path,BufferObject::texIter++));
}

void BufferObject::addBufferVertexAttrib(std::string name, int size, int offset)
{
    if(buffers.count(name) > 0)
        buffers[name]->addVertexAttribPointer(attribIter++,size,offset);
    else
        std::cout << "Buffer" << name << " not set" << std::endl;
}

void BufferObject::bindTextures()
{
    for(auto texture: textures)
    {
        (texture.second)->bind();
    }
}
void BufferObject::init(GLenum drawType)
{
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    assert(checkGLError);
    for(auto buffer: buffers)
        (buffer.second)->init(drawType);
    indexBuffer.init(drawType);
    for(auto texture: textures)
        (texture.second)->init();
    if(indexBuffer.hasData())
        indexBuffer.init();

    glBindVertexArray(0);
}

void BufferObject::render(GLenum drawType, int numVertices)
{
    bindTextures();
    assert(checkGLError);
    bindVAO();
    for(auto buffer: buffers)
    {
        buffer.second->render(drawType,numVertices,indexBuffer.hasData());
        assert(checkGLError);
    }
    unbindVAO();
    assert(checkGLError);
}
