//
// Created by lejonmcgowan on 9/23/15.
//

#ifndef TESTPROJECT2_LIGHTINGBASICSCENE_H
#define TESTPROJECT2_LIGHTINGBASICSCENE_H


#include "scene.h"

class LightingBasicScene: public Scene
{
private:
    ShaderManager shaders;
public:
    LightingBasicScene();

    virtual void update() override;

    virtual void render() override;

    virtual void init(GLFWwindow *window) override;

    virtual void processKeys(Keyboard &keyboard) override;

    virtual void processMouse(Mouse &mouse) override;
};


#endif //TESTPROJECT2_LIGHTINGBASICSCENE_H
