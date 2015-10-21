//
// Created by lejonmcgowan on 9/23/15.
//

#ifndef TESTPROJECT2_LIGHTINGBASICSCENE_H
#define TESTPROJECT2_LIGHTINGBASICSCENE_H


#include "graphics/drawables/Drawable.h"
#include "math/Camera.h"
#include "graphics/PhongMaterial.h"
#include "scene.h"

class LightingBasicScene: public Scene
{
private:
    ShaderManager shaders;
    std::map<std::string, Drawable *> objects;
    Camera camera;
public:
    virtual void render() override;
    virtual void init(GLFWwindow *window) override;
    virtual bool processKeys(Keyboard &keyboard) override;
    virtual bool processMouse(Mouse &mouse) override;
};


#endif //TESTPROJECT2_LIGHTINGBASICSCENE_H
