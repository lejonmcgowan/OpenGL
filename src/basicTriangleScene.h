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

    GLfloat vertices[12] = {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    GLuint indices[6] {
            0,1,2,
            2,3,0
    };
    GLuint texture;
    GLfloat texCoords[8] = {
            0.0f, 1.0f,  // Lower-left corner
            1.0f, 1.0f,  // Lower-right corner
            1.0f, 0.0f,   // Top-center corner
            0.0f,0.0f
    };
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
