//
// Created by lejonmcgowan on 6/26/15.
//

#ifndef BASICTRIANGLESCENE_H
#define BASICTRIANGLESCENE_H

#include "scene.h"

class BasicTriangleScene: public Scene
{
private:
    GLuint vao, vbo, ibo, tbo;
    GLfloat verticies[12] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    GLuint indices[6] {
            0,1,2,
            1,2,3
    };
    GLuint texture;
    GLfloat texCoords[6] = {
            0.0f, 0.0f,  // Lower-left corner
            1.0f, 0.0f,  // Lower-right corner
            0.5f, 1.0f   // Top-center corner
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
