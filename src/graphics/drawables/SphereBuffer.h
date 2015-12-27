//
// Created by lejonmcgowan on 9/13/15.
//

#ifndef TESTPROJECT2_BUFFERSPHERE_H
#define TESTPROJECT2_BUFFERSPHERE_H


#include <GL/glew.h>
#include "Drawable.h"
#include "ObjectBuffer.h"

class BufferSphere: public Drawable
{
private:
    BufferObject bufferObject;
    GLuint nVerts, elements;
    float radius;
    GLuint slices, stacks;

    void generateVerts(float * , float * ,float *, int *);

public:
    BufferSphere(float radius, GLuint sl, GLuint st);

    void render();
};


#endif //TESTPROJECT2_BUFFERSPHERE_H
