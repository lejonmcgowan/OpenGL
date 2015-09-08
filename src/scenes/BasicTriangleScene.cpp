//
// Created by lejonmcgowan on 8/28/15.
//

#include "BasicTriangleScene.h"
#include "utils/debugGL.h"
#include "utils/PathFind.h"

GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left
        0.5f, -0.5f, 0.0f, // Right
        0.0f,  0.5f, 0.0f  // Top
};
GLfloat colors[] = {1.0f,0.0f,0.0f,
                        0.0f,1.0f,0.0f,
                        0.0f,0.0f,1.0f};

float bgcolor[] = {0.4f,0.3f,0.3f};

void BasicTriangleScene::init(GLFWwindow* window)
{
    Scene::init(window);

    tweakBar = TwNewBar("settings");
    vertexBuffer = new Buffer(3);
    colorBuffer = new Buffer(3);
    vertexBuffer->addVertexAttribPointer(0,3,0);
    colorBuffer->addVertexAttribPointer(1,3,0);
    vertexBuffer->addData(vertices,sizeof(vertices) / sizeof(GLfloat));
    colorBuffer->addData(colors,sizeof(colors) / sizeof(GLfloat));

    shader = new Shader(PathFind::getAsset("shd/triangle.vert"), PathFind::getAsset("shd/triangle.frag"));
    shader->bind();

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
        vertexBuffer->init();
        colorBuffer->init();
    glBindVertexArray(0);

    TwAddVarRW(tweakBar, "Background Color", TW_TYPE_COLOR3F, &bgcolor, " label='Background Color' ");

    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
    glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW3);
    glfwSetCharModsCallback(window, (GLFWcharmodsfun) TwEventCharModsGLFW3);
    glfwSetCursorPosCallback(window,(GLFWcursorposfun)TwEventCursorPosGLFW3);
    glfwSetScrollCallback(window,(GLFWscrollfun)TwEventScrollGLFW3);
}

void BasicTriangleScene::render()
{
    Scene::render();
    glClearColor(bgcolor[0],bgcolor[1],bgcolor[2],1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    TwDraw();

    shader->bind();
        glBindVertexArray(VAO);
              glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);
    shader->unbind();
}

