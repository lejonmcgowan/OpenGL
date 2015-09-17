#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "math/Transform.h"

class Drawable
{
private:
    Transform transform;
public:
    Drawable(){};

    virtual void render() = 0;
    Transform& getTransform(){ return transform;}
};

#endif // DRAWABLE_H