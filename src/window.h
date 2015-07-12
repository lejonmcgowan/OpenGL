#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include<iostream>

#include "basicTriangleScene.h"

class Window
{
private:
    const int WINDOW_WIDTH, WINDOW_HEIGHT;
    const std::string WINDOW_NAME;
    GLFWwindow *window;
    Scene* scene;

public:
    Window(int width,int height, std::string name = "window");
    void init(Scene* scene);
    void run();
    void stop();
};

#endif // WINDOW_H
