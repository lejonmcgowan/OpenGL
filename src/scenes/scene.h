#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/shaderManager.h"
#include "../input/Keyboard.hpp"
#include "../input/Mouse.h"
#include <vector>

class Scene
{
protected:
    ShaderManager shaders;
    const GLFWwindow* window;
public:
    Scene(){};
    virtual void update(){}
    virtual void render() {}
    virtual void init(GLFWwindow* window) {this->window = window;}
    virtual void processKeys(Keyboard& keyboard) {}
    virtual void processMouse(Mouse& mouse){}

};

#endif // SCENE_H
