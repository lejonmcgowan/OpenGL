#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AntTweakBar.h"

#include "graphics/ShaderManager.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include <vector>

class Scene
{
protected:
    ShaderManager shaders;
    GLFWwindow* window;
    std::vector<TwBar *> tweakBars;
public:
    Scene(){};
    virtual void update(){}
    virtual void render() {}
    virtual void init(GLFWwindow* window) {this->window = window;}
    virtual bool processKeys(Keyboard &keyboard)
    {
        return false;
    }
    virtual bool processMouse(Mouse &mouse)
    {
        return false;
    }

};

#endif // SCENE_H
