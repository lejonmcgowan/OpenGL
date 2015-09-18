//
// Created by lejonmcgowan on 7/11/15.
//

#include <iostream>
#include "BufferObject.h"
#include "utils/debugGL.h"

void BufferObject::addBuffer(std::string name, int blockSize)
{
    buffers.emplace(name,new Buffer(blockSize));
}

void BufferObject::addBufferVertexAttrib(std::string name, int size, int offset, int index)
{
    if(buffers.count(name) > 0)
        buffers[name]->addVertexAttribPointer(index,size,offset);
    else
        std::cout << "Buffer" << name << " not set" << std::endl;
}

void BufferObject::init(GLenum drawType)
{
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    assert(checkGLError);
    for(auto buffer: buffers)
        (buffer.second)->init(drawType);
    indexBuffer.init(drawType);
    if(indexBuffer.hasData())
        indexBuffer.init();

    glBindVertexArray(0);
}

void BufferObject::render(GLenum drawType, int numVertices)
{
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
