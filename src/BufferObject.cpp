//
// Created by lejonmcgowan on 7/11/15.
//

#include <iostream>
#include "BufferObject.h"

void BufferObject::addBuffer(std::string name, GLuint type)
{
    if(buffers.count(name) == 0)
        buffers[name] = Buffer();
}

void BufferObject::addTexture(std::string name, std::string path)
{
    if(textures.count(name) == 0)
        textures[name] = Texture(path, texIter++);

}

void BufferObject::addBufferVertexAttrib(std::string name, int size, int numFloatsPerElement, int offset)
{
    if(buffers.count(name) > 0)
        buffers[name].addVertexAttribPointer(attribIter++,size,numFloatsPerElement,offset);
    else
        std::cout << "Buffer" << name << " not set" << std::endl;
}

void BufferObject::init(GLenum drawType = GL_STATIC_DRAW)
{
    glGenVertexArrays(1,&vao);
    for(auto buffer: buffers)
        buffer.second.init(drawType);
    indexBuffer.init(drawType);
    for(auto texture: textures)
        texture.second.init();
}
