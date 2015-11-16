//
// Created by lejonmcgowan on 11/2/15.
//

#include <src/graphics/drawables/PlaneBuffer.h>
#include <src/graphics/drawables/BufferTeapot.h>
#include <src/utils/TweakBarHelper.h>
#include <src/graphics/drawables/BufferSphere.h>
#include <src/utils/LightHelper.h>
#include <src/utils/PathFind.h>
#include "MultipleLightsScene.h"

std::vector<PhongMaterial> materials;
void MultipleLightsScene::update()
{
    Scene::update();
}
int lightMeshIter;
void MultipleLightsScene::render()
{
    Scene::render();
    int i = lightMeshIter;
    shaders.setShader("multiLight");
    for(Light& light: lights)
    {
        materials[i].setAmbient(light.getAmbient());
        materials[i].setDiffuse(light.getDiffuse());
        materials[i].setSpecular(light.getSpecular());

        LightHelper::setLightColorFromMaterial(light,materials[i]);
        LightHelper::makeLightStructUniform(light,shaders,true);
    }
}

void MultipleLightsScene::init(GLFWwindow *window)
{
    Scene::init(window);

    //setup drawables
    drawables.push_back(new PlaneBuffer(10,10,10,10));
    drawables[0]->getTransform().translateBy(glm::vec3(0.0f,-0.02f,0.0f));
    drawables.push_back(new BufferSphere(1,20,20));

    lightMeshIter = (int)drawables.size();

    //setup shading and mesh materials
    Shader multiLight(findShader("multiLights.vert"), findShader("multiLights.frag"));
    Shader basic(findShader("basic.vert"), findShader("basic2.frag"));
    shaders.addShader("simpleColor",basic);
    shaders.addShader("multiLight",multiLight);
    materials.push_back(PhongMaterial(PhongMaterialFactory::WHITE));
    materials.push_back(PhongMaterial(PhongMaterialFactory::WHITE));

    //setup lights
    lights.push_back(Light(LightType::Directional,glm::vec3(-1.0f,-1.0f,0)));

    //setup tweak bar and lighting meshes
    tweakBars.push_back(TwNewBar("Options"));

    for(Light& light: lights)
    {
        if(light.getLightType() != Directional)
        {
            TweakBarHelper::addLight(tweakBars[0], light);
            drawables.push_back(new BufferSphere(10, 10, 10));
            materials.push_back(PhongMaterial(PhongMaterialFactory::WHITE));
        }
    }
    int i = 0;
    for(auto drawable: drawables)
    {
        TweakBarHelper::addTransform(tweakBars[0],drawable->getTransform());
        TweakBarHelper::addMaterial(tweakBars[0],materials[i++]);
    }

}

bool MultipleLightsScene::processKeys(Keyboard &keyboard)
{
    return Scene::processKeys(keyboard);
}

bool MultipleLightsScene::processMouse(Mouse &mouse)
{
    return Scene::processMouse(mouse);
}
