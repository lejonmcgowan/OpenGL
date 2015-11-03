//
// Created by lejonmcgowan on 11/2/15.
//

#ifndef TESTPROJECT2_MULTIPLELIGHTSSCENE_H
#define TESTPROJECT2_MULTIPLELIGHTSSCENE_H

#include "scene.h"

class MultipleLightsScene: public Scene
{

public:
    virtual void update() override;

    virtual void render() override;

    virtual void init(GLFWwindow *window) override;

    virtual bool processKeys(Keyboard &keyboard) override;

    virtual bool processMouse(Mouse &mouse) override;
};

#endif //TESTPROJECT2_MULTIPLELIGHTSSCENE_H
