//
// Created by lejonmcgowan on 9/23/15.
//

#include "LightingBasicScene.h"

LightingBasicScene::LightingBasicScene() : Scene()
{

}

void LightingBasicScene::update()
{
    Scene::update();
}

void LightingBasicScene::render()
{
    Scene::render();
}

void LightingBasicScene::init(GLFWwindow *window)
{
    Scene::init(window);
}

void LightingBasicScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);
}

void LightingBasicScene::processMouse(Mouse &mouse)
{
    Scene::processMouse(mouse);
}
