#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "math/Transform.h"

class Drawable
{
protected:
    Transform transform;
    int VAOHandle;
public:
    Drawable(){};

    virtual void render() = 0;
    virtual int getVAO(){return VAOHandle;};
    Transform& getTransform(){ return transform;}
};

#endif // DRAWABLE_H