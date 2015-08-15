//
// Created by lejonmcgowan on 6/26/15.
//

#ifndef BASICTRIANGLESCENE_H
#define BASICTRIANGLESCENE_H

#include "scene.h"
#include "BufferObject.h"
#include "debugGL.h"

class BasicTriangleScene: public Scene
{
private:
    BufferObject object;
public:
    virtual void render() override;
    virtual void init() override;
    void switchShaders()
    {
        std::string nextShaderName = shaders.getCurrentShaderName() == "basic" ? "basic2" : "basic1";
        shaders.setShader(nextShaderName);
    }
};


#endif //BASICTRIANGLESCENE_H
