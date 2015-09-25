//
// Created by lejonmcgowan on 9/23/15.
//

#include <src/utils/PathFind.h>
#include <src/graphics/drawables/PlaneBuffer.h>
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

    objects.push_back(new PlaneBuffer(10,10,10,10));
}

bool LightingBasicScene::processKeys(Keyboard &keyboard)
{
    if(!Scene::processKeys(keyboard))
    {
        //stuuffff
    }

    return true;
}

bool LightingBasicScene::processMouse(Mouse &mouse)
{
    if(!Scene::processMouse(mouse))
    {
        //stuff...
    }

    return true;
}
