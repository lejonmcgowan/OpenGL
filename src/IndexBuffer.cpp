//
// Created by lejonmcgowan on 7/12/15.
//

#include "IndexBuffer.h"

void IndexBuffer::init(GLenum  drawType)
{
    if(bufferData.size() > 0)
    {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferData.size() * sizeof(GLuint), &bufferData[0], drawType);
    }
}