#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "BasicBillboardScene.h"
#include "input/Keyboard.hpp"

class Window
{
private:
    const std::string WINDOW_NAME;
    const int WINDOW_WIDTH, WINDOW_HEIGHT;
    GLFWwindow *window;
    Scene* scene;
    Keyboard keyboard;

public:
    Window(int width,int height, std::string name = "window");
    void init(Scene* scene);
    void run();
    void stop();
    void processKeys();
};

#endif // WINDOW_H
