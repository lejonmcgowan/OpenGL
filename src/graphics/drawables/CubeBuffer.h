//
// Created by lejonmcgowan on 9/16/15.
//

#ifndef TESTPROJECT2_BUFFERCUBE_H
#define TESTPROJECT2_BUFFERCUBE_H

#include <GL/glew.h>
#include "ObjectBuffer.h"
#include "Drawable.h"

class BufferCube: public Drawable
{
private:
    BufferObject bufferObject;
public:
    BufferCube();
    virtual void render();
};


#endif //TESTPROJECT2_BUFFERCUBE_H
