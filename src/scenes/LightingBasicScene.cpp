//
// Created by lejonmcgowan on 9/23/15.
//

#include <src/utils/PathFind.h>
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
    Shader basicLighting(PathFind::getAsset("shd/basiclighting.vert"), PathFind::getAsset("shd/basiclighting.frag"));
    shaders.addShader("basicLighting", basicLighting);
}

void LightingBasicScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);
}

void LightingBasicScene::processMouse(Mouse &mouse)
{
    Scene::processMouse(mouse);
}
