//
// Created by lejonmcgowan on 8/28/15.
//

#include "BasicTriangleScene.h"
#include "../utils/debugGL.h"

GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left
        0.5f, -0.5f, 0.0f, // Right
        0.0f,  0.5f, 0.0f  // Top
};
GLfloat colors[] = {1.0f,0.0f,0.0f,
                        0.0f,1.0f,0.0f,
                        0.0f,0.0f,1.0f};

void BasicTriangleScene::init()
{
    Scene::init();

    vertexBuffer = new Buffer(3);
    colorBuffer = new Buffer(3);
    vertexBuffer->addVertexAttribPointer(0,3,0);
    colorBuffer->addVertexAttribPointer(1,3,0);
    vertexBuffer->addData(vertices,sizeof(vertices) / sizeof(GLfloat));
    colorBuffer->addData(colors,sizeof(colors) / sizeof(GLfloat));

    std::string srcPath = __FILE__;
    srcPath = srcPath.substr(0,srcPath.rfind('/') + 1);
    std::string vertexPath("../shd/triangle.vert");
    std::string fragmentPath("../shd/triangle.frag");

    shader = new Shader(srcPath + vertexPath, srcPath + fragmentPath);
    shader->bind();

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
        vertexBuffer->init();
        colorBuffer->init();
    glBindVertexArray(0);
}

void BasicTriangleScene::render()
{
    Scene::render();
    glClearColor(0.3f,0.3f,0.3f,0.6f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->bind();
        glBindVertexArray(VAO);
              glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);
    shader->unbind();
}
