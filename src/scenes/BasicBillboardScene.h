//
// Created by lejonmcgowan on 6/26/15.
//

#ifndef BASICTRIANGLESCENE_H
#define BASICTRIANGLESCENE_H

#include "Scene.h"
#include "graphics/drawables/ObjectBuffer.h"
#include "utils/DebugGL.h"
#include "math/Camera.h"

class BasicBillboardScene : public Scene
{
private:
    Camera camera;
    BufferObject object;
public:
    virtual void render() override;
    virtual void init(GLFWwindow* window) override;
    virtual bool processKeys(Keyboard &keyboard) override;
    virtual bool processMouse(Mouse &keyboard) override;
};


#endif //BASICTRIANGLESCENE_H
