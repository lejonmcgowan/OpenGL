#ifndef SCENE_H
#define SCENE_H

#include "shaderManager.h"
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
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void init(){}
};

#endif // SCENE_H
