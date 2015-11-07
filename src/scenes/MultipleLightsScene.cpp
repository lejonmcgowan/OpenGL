//
// Created by lejonmcgowan on 11/2/15.
//

#include <src/graphics/drawables/PlaneBuffer.h>
#include <src/graphics/drawables/BufferTeapot.h>
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


    drawables.push_back(new PlaneBuffer(10,10,10,10));
    drawables[0]->getTransform().translateBy(glm::vec3(0.0f,-0.02f,0.0f));
    drawables.push_back(new BufferTeapot(20,glm::mat4()));

    lights.push_back(Light(LightType::Directional,glm::vec3(-1.0f,-1.0f,0)));
    tweakBars.push_back(TwNewBar("Options"));

}

bool MultipleLightsScene::processKeys(Keyboard &keyboard)
{
    return Scene::processKeys(keyboard);
}

bool MultipleLightsScene::processMouse(Mouse &mouse)
{
    return Scene::processMouse(mouse);
}
