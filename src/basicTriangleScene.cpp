//
// Created by lejonmcgowan on 6/26/15.
//

#include "basicTriangleScene.h"

#include <iostream>
#include <assert.h>

GLfloat vertices[12] = {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
};
GLuint indices[6] {
        0,1,2,
        2,3,0
};
GLuint texture;
GLfloat texCoords[8] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        2.0f, 0.0f,
        0.0f,0.0f
};

void BasicTriangleScene::render()
{
    Scene::render();

    assert(checkGLError);
    shaders.bind();
    assert(checkGLError);

    glActiveTexture(GL_TEXTURE0);
    shaders.setUniform("textureColor1", object.getTexture("container").getTexIndex());
    shaders.setUniform("textureColor2", object.getTexture("awesome").getTexIndex());
    object.bindTextures();
    assert(checkGLError);
    glBindVertexArray(object.getVAO());
    assert(checkGLError);

    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
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
    object.addBuffer("vbo", 3);
    object.getBuffer("vbo").addData(vertices, sizeof(vertices) / sizeof(GLfloat));
    object.addBufferVertexAttrib("vbo",3,0);

    object.addBuffer("tbo", 2);
    object.getBuffer("tbo").addData(texCoords, sizeof(texCoords) / sizeof(GLfloat));
    object.addBufferVertexAttrib("tbo",2,0);

    object.addTexture("container",srcPath + "assets/container.jpg");
    object.addTexture("awesome",srcPath + "assets/awesomeface.png");

    object.getIndexBuffer().addData(indices, sizeof(indices) / sizeof(GLuint));

    object.init(GL_STATIC_DRAW);


    shaders.bind(); //for nonchanging uniforms
        shaders.setUniform("myColor",glm::vec4(1.0f,1.0f,0.0f,1.0f));
        shaders.setUniform("textureColor",0);
    shaders.unbind();
}

void BasicTriangleScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);
}
