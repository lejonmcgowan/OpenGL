//
// Created by lejonmcgowan on 9/23/15.
//

#include <src/utils/PathFind.h>
#include <src/graphics/drawables/PlaneBuffer.h>
#include <src/graphics/drawables/BufferSphere.h>
#include <src/graphics/TextureManager.h>
#include <src/utils/debugGL.h>
#include <src/graphics/drawables/BufferCube.h>
#include "LightingBasicScene.h"

PhongMaterial surfaceMaterial = PhongMaterialFactory::JADE;
PhongMaterial lightMaterial   = PhongMaterialFactory::WHITE;

void addMaterialToTweakBar(TwBar* bar, PhongMaterial& material, std::string name = "")
{
    static bool defined = false;
    static TwType TW_TYPE_MATERIAL;
    if(!defined)
    {
        //setup TwStruct for Material
        TwStructMember materialMembers[] = // array used to describe tweakable variables of the Light structure
                {
                        {"Ambient",     TW_TYPE_COLOR3F, 0 * sizeof(glm::vec3), " "},
                        {"DIffuse",     TW_TYPE_COLOR3F, 1 * sizeof(glm::vec3), " "},
                        {"Specular",    TW_TYPE_COLOR3F, 2 * sizeof(glm::vec3), " "},
                        {"specularExp", TW_TYPE_FLOAT,   3 * sizeof(glm::vec3),     " min=0 max=256 step= 2 help='shininess' "}
                };
        // create a new TwType associated to the struct defined by the lightMembers array
        TW_TYPE_MATERIAL = TwDefineStruct("Material", materialMembers, 4, 3 * sizeof(glm::vec3) + sizeof(float),
                                                 NULL, NULL);
        defined = true;
    }

    static int numMaterials = 0;
    numMaterials++;
    if(name.empty())
        name = "Material " + std::to_string(numMaterials);
    //plz work...
    TwAddVarRW(bar,name.c_str(),TW_TYPE_MATERIAL,&material," group='Materials' ");
}

void addTransformToTweakBar(TwBar* bar, Transform& transform, std::string name = "")
{
    static bool defined = false;
    static TwType TW_TYPE_TRANSFORM;
    if(!defined)
    {
        //setup TwStruct for Material
        TwStructMember transformMembers[] = // array used to describe tweakable variables of the Light structure
                {
                        {"Translation",  TW_TYPE_DIR3F, 0 * sizeof(glm::vec3), " "},
                        {"Rotation",     TW_TYPE_DIR3F, 1 * sizeof(glm::vec3), " "},
                        {"Scale",        TW_TYPE_DIR3F, 2 * sizeof(glm::vec3), " "}
                };
        // create a new TwType associated to the struct defined by the lightMembers array
        TW_TYPE_TRANSFORM = TwDefineStruct("Transform", transformMembers, 3, 3 * sizeof(glm::vec3),
                                          NULL, NULL);
        defined = true;
    }

    static int numTransforms = 0;
    numTransforms++;
    if(name.empty())
        name = "Transform " + std::to_string(numTransforms);
    //plz work...
    TwAddVarRW(bar,name.c_str(),TW_TYPE_TRANSFORM,&transform," group='Transforms' ");
}

void LightingBasicScene::render()
{
    glClearColor(0.5f,0.5f,0.5f,0.7f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    assert(checkGLError);

    Scene::render();

    shaders.setShader("basic");
    shaders.bind();
        shaders.setUniform("myColor", lightMaterial.getDiffuse());

        shaders.setUniform("projection", camera.getPerspectiveMatrix());
        shaders.setUniform("view", camera.getViewMatrix());
        shaders.setUniform("model", objects["lightSphere"]->getTransform().getTransformMatrix());
        objects["lightSphere"]->render();
    shaders.unbind();
    assert(checkGLError);

    shaders.setShader("basicLighting");
    shaders.bind();
        lightMaterial.setMaterialUniform(shaders,"lightMaterial");
        shaders.setUniform("lightPos", objects["lightSphere"]->getTransform().getTranslation());
        shaders.setUniform("viewPos", camera.getTranslation());
        surfaceMaterial.setMaterialUniform(shaders,"material");

        shaders.setUniform("model",objects["sphere"]->getTransform().getTransformMatrix());
        shaders.setUniform("view", camera.getViewMatrix());
        shaders.setUniform("projection", camera.getPerspectiveMatrix());
        assert(checkGLError);
    objects["sphere"]->render();
    shaders.unbind();

    shaders.setShader("texturedLighting");
    shaders.bind();
        TextureManager::bindTextures();
        shaders.setUniform("texIndex", texIndex("checkerboard"));
        assert(checkGLError);

        shaders.setUniform("lightColor", lightMaterial.getDiffuse());
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

    surfaceMaterial = PhongMaterialFactory::PEARL;
    lightMaterial   = PhongMaterialFactory::WHITE;
    Shader basicLighting(findShader("basicLighting.vert"), findShader("basicLighting2.frag"));
    Shader texturedLighting(findShader("basicLighting.vert"), findShader("texturedLighting.frag"));
    Shader basic(findShader("basic.vert"), findShader("basic2.frag"));
    shaders.addShader("basicLighting", basicLighting);
    shaders.addShader("basic", basic);
    shaders.addShader("texturedLighting", texturedLighting);

    TextureManager::addTexture("checkerboard", findAsset("checkerboard.png"));

    TextureManager::init();


    objects["plane"] = new PlaneBuffer(10,10,10,10,5,5);
    objects["plane"]->getTransform().translateBy(glm::vec3(0.0f,-0.5f,0.0f));
    objects["sphere"] = new BufferCube();
    objects["lightSphere"] = new BufferSphere(0.5f,20,20);
    objects["lightSphere"]->getTransform().translateTo(glm::vec3(5.0f,2.0f,2.0f));

    tweakBars.push_back(TwNewBar("Material Colors"));
    addMaterialToTweakBar(tweakBars[0],surfaceMaterial,"Shape Material");
    addMaterialToTweakBar(tweakBars[0],lightMaterial,"Light Material");
    addTransformToTweakBar(tweakBars[0],objects["sphere"]->getTransform(),"Shape Transform");
    addTransformToTweakBar(tweakBars[0],objects["lightSphere"]->getTransform(),"Light Transform");
    TwDefine(" GLOBAL fontsize=3 "); // use large font
}
bool cursorEnabled = true;
bool LightingBasicScene::processKeys(Keyboard& keyboard)
{
    if(keyboard.keySinglePressed('V'))
    {
        cursorEnabled = !cursorEnabled;
        if(cursorEnabled)
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    }

    Camera::WASDMove(camera,keyboard,0.05f);

    return true;
}

bool LightingBasicScene::processMouse(Mouse& mouse)
{
    if(!cursorEnabled || mouse.getMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        Camera::WASDLook(camera,mouse,0.03f);

    Camera::FOVScroll(camera, mouse, 0.1f);

    return true;
}
