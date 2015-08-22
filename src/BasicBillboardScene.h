//
// Created by lejonmcgowan on 6/26/15.
//

#ifndef BASICTRIANGLESCENE_H
#define BASICTRIANGLESCENE_H

#include "scene.h"
#include "graphics/BufferObject.h"
#include "utils/debugGL.h"
#include "math/Camera.h"

class BasicTriangleScene: public Scene
{
private:
    Camera camera;
    BufferObject object;
public:
    virtual void render() override;
    virtual void init() override;
    virtual void processKeys(Keyboard& keyboard) override;
};


#endif //BASICTRIANGLESCENE_H
