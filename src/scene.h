#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/shaderManager.h"
#include "input/Keyboard.hpp"
#include "input/Mouse.h"
#include <vector>

class Scene
{
protected:
    ShaderManager shaders;
public:
    Scene(){};
    virtual void update(){}
    virtual void render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    virtual void init(){}
    virtual void processKeys(Keyboard& keyboard) {}
    virtual void processMouse(Mouse& mouse){}

};

#endif // SCENE_H
