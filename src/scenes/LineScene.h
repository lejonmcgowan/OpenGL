//
// Created by lejonmcgowan on 8/30/15.
//

#ifndef TESTPROJECT2_LINESCENE_H
#define TESTPROJECT2_LINESCENE_H

#include "scene.h"
#include "graphics/Buffer.h"
#include "math/Camera.h"

class LineScene: public Scene
{
private:
    Buffer* lineBuffer, *colorBuffer, *normalBuffer;
    Camera*camera;
    Transform* lineTransform;
    Shader* shader;
    GLuint VAO;
public:
    LineScene():lineBuffer(new Buffer(2)),
                colorBuffer(new Buffer(3)),
                normalBuffer(new Buffer(2)),
                camera(new Camera()),
                lineTransform(new Transform()),
                shader(new Shader())
    {

    }
    virtual void render() override;
    virtual void init(GLFWwindow* window)  override;
    virtual bool processKeys(Keyboard &keyboard) override;
    virtual bool processMouse(Mouse &mouse) override;

    void makeBufferLine(glm::highp_vec2 point1, glm::highp_vec2 point2, float thickness);
};


#endif //TESTPROJECT2_LINESCENE_H
