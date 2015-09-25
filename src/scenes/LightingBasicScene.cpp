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

    objects["plane"] = new PlaneBuffer(10,10,10,10);
    objects["plane"]->getTransform().translateBy(glm::vec3(0.0f,-0.5f,0.0f));
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
