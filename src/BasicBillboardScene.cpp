//
// Created by lejonmcgowan on 6/26/15.
//

#include "BasicBillboardScene.h"

#include <iostream>
#include <assert.h>

GLfloat vertices_OLD[12] = {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
};

GLfloat vertices[180] = {
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

void BasicTriangleScene::render()
{
    Scene::render();

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
        glBindVertexArray(object.getVAO());
        assert(checkGLError);

        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        assert(checkGLError);

        glBindVertexArray(0);
        assert(checkGLError);
    shaders.unbind();
}

void BasicTriangleScene::init() {
    //TODO: clean up string parsing for path
    Scene::init();
    std::string srcPath = __FILE__;
    srcPath = srcPath.substr(0,srcPath.rfind('/') + 1);
    std::string vertexPath("shd/basic.vert");
    std::string fragmentPath2("shd/basic2.frag");
    std::string fragmentPath("shd/basic.frag");
    std::cout << "making shader" << std::endl;
    Shader basic(srcPath + vertexPath,srcPath + fragmentPath);
    Shader basic2(srcPath + vertexPath,srcPath + fragmentPath2);
    shaders.addShader("basic",basic);
    shaders.addShader("basic2",basic2);
    shaders.setShader("basic");

    std::cout << "starting binding"<< std::endl;
    object.addBuffer("uberBuffer", 5);
    object.getBuffer("uberBuffer").addData(vertices, sizeof(vertices) / sizeof(GLfloat));
    object.addBufferVertexAttrib("uberBuffer",3,0);
    object.addBufferVertexAttrib("uberBuffer",2, 3);

    object.addTexture("container",srcPath + "assets/container.jpg");
    object.addTexture("awesome",srcPath + "assets/awesomeface.png");


    object.init(GL_STATIC_DRAW);


    shaders.bind(); //for nonchanging uniforms
        shaders.setUniform("myColor",glm::vec4(1.0f,1.0f,0.0f,1.0f));
        shaders.setUniform("textureColor",0);
    shaders.unbind();
}

void BasicTriangleScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);

    if(keyboard.keyPressed('W'))
    {
        object.getTransform().translateBy(glm::vec3(0.0f, 0.01f, 0.0f));
    }
    if(keyboard.keyPressed('A'))
    {
        object.getTransform().translateBy(glm::vec3(-0.01f, 0.0f, 0.0f));
    }
    if(keyboard.keyPressed('S'))
    {
        object.getTransform().translateBy(glm::vec3(0.0f, -0.01f, 0.0f));
    }
    if(keyboard.keyPressed('D'))
    {
        object.getTransform().translateBy(glm::vec3(0.01f, 0.0f, 0.0f));
    }

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
