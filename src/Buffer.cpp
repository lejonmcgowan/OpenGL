//
// Created by lejonmcgowan on 7/11/15.
//

#include "Buffer.h"

GLuint Buffer::addVertexAttribPointer(int attribPointerIndex, int elementSize, int blockSize, int offset)
{
    attribPointerData.push_back(AttribPointerData(attribPointerIndex,elementSize,blockSize,offset));
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
    glBindBuffer(GL_ARRAY_BUFFER,handle);
    glBufferData(GL_ARRAY_BUFFER,bufferData.size() * sizeof(GL_FLOAT), &bufferData[0],drawType);
    for(int i = 0; i < attribPointerData.size(); i++)
    {
        auto pointerData = attribPointerData[i];

        glVertexAttribPointer(pointerData.index,pointerData.elementSize,GL_FLOAT,GL_FALSE,
                              pointerData.blockSize,(GLvoid *)(pointerData.offset));
        glEnableVertexAttribArray(pointerData.index);
    }
}