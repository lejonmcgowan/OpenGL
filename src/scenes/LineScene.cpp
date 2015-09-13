//
// Created by lejonmcgowan on 8/30/15.
//

#include <src/utils/PathFind.h>
#include "LineScene.h"
#include <vector>

//GLfloat linePoints[] = {0.0f,0.0f,
//                        0.25f,0.25f,
//                        0.25f,0.0f,
//                        -0.25f,0.5f,
//                        -0.5f,-0.5f,
//                        0.5f,-0.5f};

GLfloat colors[] = {1.0f,0.0f,0.0f,
                    1.0f,0.0f,0.0f,
                    1.0f,0.0f,0.0f,
                    0.0f,1.0f,0.0f,
                    0.0f,1.0f,0.0f,
                    0.0f,1.0f,0.0f};

std::vector<glm::vec2> points, thickLineBuffer;
float thickness = 0.03f;

std::vector<GLfloat> normals;

void make2PointBufferLine()
{
    thickLineBuffer.clear();
    glm::vec2 point1 = points[0];
    glm::vec2 point2 = points[1];

    glm::vec2 line = point2 - point1;
    glm::vec2 normal = glm::normalize(glm::vec2(-line.y,line.x));
    normal *= (thickness / 2);

    glm::vec2 a = point1 + normal;
    glm::vec2 b = point1 - normal;
    glm::vec2 c = point2 + normal;
    glm::vec2 d = point2 - normal;


}

void addPoint(glm::vec2 point)
{
    points.push_back(point);
    switch(points.size())
    {
        case 2: make2PointBufferLine();
    }
}

void LineScene::init(GLFWwindow *window)
{
    Scene::init(window);
    glEnable(GL_DEPTH_TEST);

    addPoint(glm::vec2(-0.5, -0.25));
    addPoint(glm::vec2(0.25, 0.75));

    lineBuffer->addData(thickLineBuffer);
    colorBuffer->addData(colors,sizeof(colors) / sizeof(GLfloat));

    lineBuffer->addVertexAttribPointer(0,2,0);
    colorBuffer->addVertexAttribPointer(1,3,0);


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
                glDrawArrays(GL_TRIANGLES,0,6);
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