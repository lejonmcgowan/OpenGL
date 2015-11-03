//
// Created by lejonmcgowan on 11/2/15.
//

#include "MultipleLightsScene.h"

void MultipleLightsScene::update()
{
    Scene::update();
}

void MultipleLightsScene::render()
{
    Scene::render();
}

void MultipleLightsScene::init(GLFWwindow *window)
{
    Scene::init(window);
}

bool MultipleLightsScene::processKeys(Keyboard &keyboard)
{
    return Scene::processKeys(keyboard);
}

bool MultipleLightsScene::processMouse(Mouse &mouse)
{
    return Scene::processMouse(mouse);
}
