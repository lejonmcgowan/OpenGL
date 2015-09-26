#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AntTweakBar.h"

#include "graphics/shaderManager.h"
#include "input/Keyboard.hpp"
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
        return TwEventKeyGLFW3(window,
                               keyboard.getLastKeyPressed(),
                               keyboard.getLastScancode(),
                               keyboard.getLastAction(),
                               keyboard.getLastMods());
    }
    virtual bool processMouse(Mouse &mouse)
    {
        bool consumed = false;
        consumed = consumed && TwEventMouseButtonGLFW3(window,mouse.getLastButton(), mouse.getLastAction(), mouse.getLastMods());
        glm::vec2 offsets = mouse.getScrollOffset();
        consumed = consumed && TwEventScrollGLFW3(window,offsets.x,offsets.y);
        glm::vec2 mousePos = mouse.getMouseOffset();
        consumed = consumed && TwEventCursorPosGLFW3(window,mousePos.x,mousePos.y);

        return consumed;
    }

};

#endif // SCENE_H
