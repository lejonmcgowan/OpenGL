//
// Created by lejonmcgowan on 7/11/15.
//

#include "Buffer.h"
#include "debugGL.h"

GLuint Buffer::addVertexAttribPointer(int attribPointerIndex, int elementSize, int offset)
{
    attribPointerData.push_back(AttribPointerData(attribPointerIndex,elementSize * sizeof(GLfloat),offset));
}

void Buffer::setAttribPointerState(int attribPointerIndex, bool enabled)
{
    if(enabled)
        glEnableVertexAttribArray(attribPointerIndex);
    else
        glDisableVertexAttribArray(attribPointerIndex);
}

void Buffer::init(GLenum  drawType)
{
    glGenBuffers(1,&handle);
    glBindBuffer(GL_ARRAY_BUFFER,handle);
    assert(checkGLError);
    glBufferData(GL_ARRAY_BUFFER,bufferData.size() * sizeof(GL_FLOAT), &bufferData[0],drawType);
    assert(checkGLError);
    for(int i = 0; i < attribPointerData.size(); i++)
    {
        auto pointerData = attribPointerData[i];

        glVertexAttribPointer(pointerData.index,blockSize,GL_FLOAT,GL_FALSE,
                              pointerData.elementSize,(GLvoid *)(pointerData.offset));
        assert(checkGLError);
        glEnableVertexAttribArray(pointerData.index);
        assert(checkGLError);
    }
    assert(checkGLError);
}