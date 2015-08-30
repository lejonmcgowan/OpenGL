//
// Created by lejonmcgowan on 8/28/15.
//

#ifndef TESTPROJECT2_BASICTRIANGLESCENE_H
#define TESTPROJECT2_BASICTRIANGLESCENE_H

#include "scene.h"
#include "graphics/Buffer.h"
#include "graphics/shader.h"

class BasicTriangleScene : public Scene
{
private:
    GLuint VAO;
    Buffer* vertexBuffer;
    Buffer* colorBuffer;
    Shader* shader;
public:
    virtual void init(GLFWwindow* window) override;
    virtual void render() override;
};


#endif //TESTPROJECT2_BASICTRIANGLESCENE_H
