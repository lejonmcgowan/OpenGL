//
// Created by lejonmcgowan on 6/26/15.
//

#include "lib/SOIL.h"

#include "basicTriangleScene.h"
#include "debugGL.h"
#include <iostream>
#include <assert.h>

void BasicTriangleScene::render()
{
    Scene::render();
    assert(checkGLError);
    shaders.bind();
    assert(checkGLError);

    //glActiveTexture(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    assert(checkGLError);

    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);
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
    glGenVertexArrays(1, &vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ibo);
    glGenBuffers(1,&tbo);
    assert(checkGLError);

    //Buffer logic. TODO: move buffer logic to own class
    glBindVertexArray(vao);
    assert(checkGLError);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verticies),verticies, GL_STATIC_DRAW);
    assert(checkGLError);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    assert(checkGLError);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE ,3 * sizeof(GLfloat),(GLvoid *)0);
    assert(checkGLError);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    assert(checkGLError);

    glBindBuffer(GL_ARRAY_BUFFER,tbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(texCoords),texCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 2 * sizeof(GLfloat),(GLvoid *)0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glEnableVertexAttribArray(1);
    assert(checkGLError);


    //testing SOIL usage. TODO: move to texture class

    int width, height;
    std::string assetPath = srcPath + "assets/container.jpg";
    unsigned char* image = SOIL_load_image(assetPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    std::cout << "(" << width << "," << height << ")" << std::endl;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    assert(checkGLError);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    assert(checkGLError);

    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D,0);
    assert(checkGLError);

    shaders.bind(); //for nonchanging uniforms
        shaders.setUniform("myColor",glm::vec4(1.0f,1.0f,0.0f,1.0f));
       // shaders.setUniform("textureColor",0);
    shaders.unbind();
}
