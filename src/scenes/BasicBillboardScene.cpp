//
// Created by lejonmcgowan on 6/26/15.
//

#include "BasicBillboardScene.h"
#include "utils/PathFind.h"

#include <iostream>
#include <assert.h>
#include <src/graphics/drawables/PlaneBuffer.h>

GLfloat vertices2[180] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

GLuint indices[6] {
        0,1,2,
        2,3,0
};
GLuint texture;
GLfloat texCoords[8] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f,0.0f
};

PlaneBuffer *planeBuffer;
void BasicBillboardScene::render()
{
    glClearColor(0.2f,0.3f,0.3f,0.6f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    assert(checkGLError);
    shaders.bind();
        assert(checkGLError);

        shaders.setUniform("textureColor1", object.getTexture("container").getTexIndex());
        shaders.setUniform("textureColor2", object.getTexture("awesome").getTexIndex());

        shaders.setUniform("model", object.getTransform().getTransformMatrix());
        shaders.setUniform("view", camera.getViewMatrix());
        shaders.setUniform("projection", camera.getPerspectiveMatrix());

        object.render(GL_TRIANGLES,36);
        planeBuffer->render();
    shaders.unbind();
}

void BasicBillboardScene::init(GLFWwindow* window) {
    //TODO: clean up string parsing for path

    glEnable(GL_DEPTH_TEST);

    Scene::init(window);

    //glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    Shader basic(PathFind::getAsset("shd/basic.vert"), PathFind::getAsset("shd/basic.frag"));
    Shader basic2(PathFind::getAsset("shd/basic.vert"), PathFind::getAsset("shd/basic2.frag"));
    shaders.addShader("basic",basic);
    shaders.addShader("basic2",basic2);
    shaders.setShader("basic");

    std::cout << "starting binding"<< std::endl;
    object.addBuffer("uberBuffer", 5);
    object.getBuffer("uberBuffer").addData(vertices2, sizeof(vertices2) / sizeof(GLfloat));
    object.addBufferVertexAttrib("uberBuffer",3,0);
    object.addBufferVertexAttrib("uberBuffer",2, 3);

    object.addTexture("container", PathFind::getAsset("container.jpg"));
    object.addTexture("awesome", PathFind::getAsset("awesomeface.png"));


    object.init();

    planeBuffer = new PlaneBuffer(5,5,5,5);

    shaders.bind(); //for nonchanging uniforms
        shaders.setUniform("myColor",glm::vec4(1.0f,1.0f,0.0f,1.0f));
        shaders.setUniform("textureColor",0);
    shaders.unbind();
}

void BasicBillboardScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);
    Camera::WASDMove(camera,keyboard,0.03f);

    if(keyboard.keyPressed('Q'))
    {
        object.getTransform().scaleIncreaseBy(-0.01f);
    }

    if(keyboard.keyPressed('E'))
    {
        object.getTransform().scaleIncreaseBy(0.01f);
    }

    if(keyboard.keyPressed('Z'))
    {
        object.getTransform().rotateBy(glm::vec3(0.0f,-0.1f, 0.0f));
    }

    if(keyboard.keyPressed('X'))
    {
        object.getTransform().rotateBy(glm::vec3(0.0f,0.1f, 0.0f));
    }

    if(keyboard.keyPressed('R'))
    {
        object.getTransform().reset();
    }
}

bool followMouse = true;
void BasicBillboardScene::processMouse(Mouse& mouse)
{
    if(mouse.getMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        followMouse = !followMouse;
    if(followMouse)
    {
        Camera::WASDLook(camera, mouse, 0.01f);
        Camera::FOVScroll(camera, mouse, 0.1f);
    }
}