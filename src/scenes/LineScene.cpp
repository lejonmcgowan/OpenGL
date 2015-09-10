//
// Created by lejonmcgowan on 8/30/15.
//

#include <src/utils/PathFind.h>
#include "LineScene.h"
#include <vector>

GLfloat linePoints[] = {0.0f,0.0f,
                        0.25f,0.25f,
                        0.25f,0.0f,
                        -0.25f,0.5f,
                        -0.5f,-0.5f,
                        0.5f,-0.5f};

GLfloat colors[] = {1.0f,0.0f,0.0f,
                    1.0f,0.0f,0.0f,
                    1.0f,0.0f,0.0f,
                    1.0f,0.0f,0.0f,
                    1.0f,0.0f,0.0f,
                    1.0f,0.0f,0.0f};

std::vector<GLfloat> normals;

void fillNormals()
{
    for(int i = 0; i < sizeof(linePoints) / sizeof(GLfloat); i+=2)
    {
        normals.push_back(-linePoints[1]);
        normals.push_back(linePoints[0]);
    }
}

void LineScene::init(GLFWwindow *window)
{
    Scene::init(window);
    glEnable(GL_DEPTH_TEST);

    lineBuffer->addData(linePoints,sizeof(linePoints) / sizeof(GLfloat));
    colorBuffer->addData(colors,sizeof(colors) / sizeof(GLfloat));
    fillNormals();
    normalBuffer->addData(normals);

    lineBuffer->addVertexAttribPointer(0,2,0);
    colorBuffer->addVertexAttribPointer(1,3,0);
    normalBuffer->addVertexAttribPointer(2,2,0);

    shader->initialize(PathFind::getAsset("shd/line.vert"),PathFind::getAsset("shd/line.frag"));

    shader->bind();
        shader->setUniform("model",lineTransform->getTransformMatrix());
        shader->setUniform("view",camera->getViewMatrix());
        shader->setUniform("projection",camera->getPerspectiveMatrix());
    shader->unbind();

    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);
        lineBuffer->init();
        colorBuffer->init();
    glBindVertexArray(0);
}

void LineScene::render()
{
    Scene::render();
    glClearColor(0.2f,0.3f,0.3f,0.6f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->bind();
        shader->setUniform("model",lineTransform->getTransformMatrix());
        shader->setUniform("view",camera->getViewMatrix());
        shader->setUniform("projection",camera->getPerspectiveMatrix());
        glBindVertexArray(VAO);
                glDrawArrays(GL_LINES,0,6);
        glBindVertexArray(0);
    shader->unbind();
}

void LineScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);
}

void LineScene::processMouse(Mouse &mouse)
{
    Scene::processMouse(mouse);
}
