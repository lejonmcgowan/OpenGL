//
// Created by lejonmcgowan on 9/12/15.
//

#ifndef TESTPROJECT2_PLANEBUFFER_H
#define TESTPROJECT2_PLANEBUFFER_H


#include "Drawable.h"
#include "BufferObject.h"

class PlaneBuffer: public Drawable
{
private:
    BufferObject bufferObject;
    int faces;

public:
    PlaneBuffer(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f);

    virtual void render();
};


#endif //TESTPROJECT2_PLANEBUFFER_H
