//
// Created by lejonmcgowan on 9/23/15.
//

#include <src/utils/PathFind.h>
#include <src/graphics/drawables/PlaneBuffer.h>
#include <src/graphics/drawables/BufferSphere.h>
#include <src/graphics/TextureManager.h>
#include <src/utils/debugGL.h>
#include "LightingBasicScene.h"

glm::vec3 lightColor = glm::vec3(1.0f,1.0f,1.0f);
void LightingBasicScene::render()
{
    glClearColor(0.5f,0.5f,0.5f,0.7f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    assert(checkGLError);

    Scene::render();

    shaders.setShader("basic");
    shaders.bind();
        shaders.setUniform("myColor", glm::vec4(lightColor, 1.0f));

        shaders.setUniform("projection", camera.getPerspectiveMatrix());
        shaders.setUniform("view", camera.getViewMatrix());
        shaders.setUniform("model", objects["lightSphere"]->getTransform().getTransformMatrix());
        objects["lightSphere"]->render();
    shaders.unbind();
    assert(checkGLError);

    shaders.setShader("basicLighting");
    shaders.bind();
        shaders.setUniform("lightColor", lightColor);
        shaders.setUniform("lightPos", objects["lightSphere"]->getTransform().getTranslation());
        shaders.setUniform("ambientColor", glm::vec3(0.0f,1.0f,1.0f));

        shaders.setUniform("model",objects["sphere"]->getTransform().getTransformMatrix());
        shaders.setUniform("view", camera.getViewMatrix());
        shaders.setUniform("projection", camera.getPerspectiveMatrix());
        objects["sphere"]->render();
    shaders.unbind();

    shaders.setShader("texturedLighting");
    shaders.bind();
        TextureManager::bindTextures();
        shaders.setUniform("texIndex", texIndex("checkerboard"));
        assert(checkGLError);

        shaders.setUniform("lightColor", lightColor);
        shaders.setUniform("lightPos", objects["lightSphere"]->getTransform().getTranslation());
        shaders.setUniform("ambientColor", glm::vec3(1.0f,1.0f,1.0f));

        shaders.setUniform("model",objects["plane"]->getTransform().getTransformMatrix());
        shaders.setUniform("view", camera.getViewMatrix());
        shaders.setUniform("projection", camera.getPerspectiveMatrix());
        objects["plane"]->render();
        TextureManager::unbindTextures();
    shaders.unbind();

    TwDraw();

    assert(checkGLError);
}

void LightingBasicScene::init(GLFWwindow *window)
{
    glEnable(GL_DEPTH_TEST);

    Scene::init(window);

    Shader basicLighting(findShader("basicLighting.vert"), findShader("basicLighting.frag"));
    Shader texturedLighting(findShader("basicLighting.vert"), findShader("texturedLighting.frag"));
    Shader basic(findShader("basic.vert"), findShader("basic2.frag"));
    shaders.addShader("basicLighting", basicLighting);
    shaders.addShader("basic", basic);
    shaders.addShader("texturedLighting", texturedLighting);

    TextureManager::addTexture("checkerboard", findAsset("checkerboard.png"));

    TextureManager::init();


    objects["plane"] = new PlaneBuffer(10,10,10,10,5,5);
    objects["plane"]->getTransform().translateBy(glm::vec3(0.0f,-0.5f,0.0f));
    objects["sphere"] = new BufferSphere(1.0f,30,30);
    objects["lightSphere"] = new BufferSphere(0.5f,20,20);
    objects["lightSphere"]->getTransform().translateTo(glm::vec3(5.0f,2.0f,2.0f));

    tweakBars.push_back(TwNewBar("Light Color"));
    TwAddVarRW(tweakBars[0],"color",TW_TYPE_COLOR3F,&lightColor," label='Lighting Color' ");
    TwDefine(" GLOBAL fontsize=3 "); // use large font
}

bool LightingBasicScene::processKeys(Keyboard& keyboard)
{
    if(!Scene::processKeys(keyboard))
    {
        //stuuffff
        Camera::WASDMove(camera,keyboard,0.03f);
    }

    return true;
}

bool LightingBasicScene::processMouse(Mouse& mouse)
{
    if(!Scene::processMouse(mouse))
    {
        //stuff...
        if(mouse.getMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
            Camera::WASDLook(camera,mouse,0.01f);

        Camera::FOVScroll(camera, mouse, 0.1f);
    }

    return true;
}
