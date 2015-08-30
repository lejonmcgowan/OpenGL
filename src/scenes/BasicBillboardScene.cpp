//
// Created by lejonmcgowan on 6/26/15.
//

#include "BasicBillboardScene.h"
#include "utils/PathFind.h"

#include <iostream>
#include <assert.h>

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

        object.bindTextures();
        assert(checkGLError);
        object.bindVAO();
        assert(checkGLError);

        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        assert(checkGLError);

        object.unbindVAO();
        assert(checkGLError);
    shaders.unbind();
}

void BasicBillboardScene::init(GLFWwindow* window) {
    //TODO: clean up string parsing for path

    glEnable(GL_DEPTH_TEST);

    Scene::init(window);

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    Shader basic(PathFind::getAsset("assets/shd/basic.vert"), PathFind::getAsset("assets/shd/basic.frag"));
    Shader basic2(PathFind::getAsset("assets/shd/basic.vert"), PathFind::getAsset("assets/shd/basic2.frag"));
    shaders.addShader("basic",basic);
    shaders.addShader("basic2",basic2);
    shaders.setShader("basic");

    std::cout << "starting binding"<< std::endl;
    object.addBuffer("uberBuffer", 5);
    object.getBuffer("uberBuffer").addData(vertices2, sizeof(vertices2) / sizeof(GLfloat));
    object.addBufferVertexAttrib("uberBuffer",3,0);
    object.addBufferVertexAttrib("uberBuffer",2, 3);

    object.addTexture("container", PathFind::getAsset("assets/container.jpg"));
    object.addTexture("awesome", PathFind::getAsset("assets/awesomeface.png"));


    object.init(GL_STATIC_DRAW);


    shaders.bind(); //for nonchanging uniforms
        shaders.setUniform("myColor",glm::vec4(1.0f,1.0f,0.0f,1.0f));
        shaders.setUniform("textureColor",0);
    shaders.unbind();
}

void BasicBillboardScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);
    Camera::WASDMove(camera,keyboard,0.03f);
//    if(keyboard.keyPressed('W'))
//    {
//        object.getTransform().translateBy(glm::vec3(0.0f, 0.01f, 0.0f));
//    }
//    if(keyboard.keyPressed('A'))
//    {
//        object.getTransform().translateBy(glm::vec3(-0.01f, 0.0f, 0.0f));
//    }
//    if(keyboard.keyPressed('S'))
//    {
//        object.getTransform().translateBy(glm::vec3(0.0f, -0.01f, 0.0f));
//    }
//    if(keyboard.keyPressed('D'))
//    {
//        object.getTransform().translateBy(glm::vec3(0.01f, 0.0f, 0.0f));
//    }

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

void BasicBillboardScene::processMouse(Mouse& mouse)
{
    Camera::WASDLook(camera,mouse,0.01f);
    Camera::FOVScroll(camera,mouse,0.1f);
}