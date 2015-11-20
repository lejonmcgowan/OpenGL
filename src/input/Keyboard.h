//
// Created by lejonmcgowan on 8/16/15.
//

#ifndef TESTPROJECT2_KEYBOARD_HPP
#define TESTPROJECT2_KEYBOARD_HPP

#include <GLFW/glfw3.h>
#include <ext/include/AntTweakBar.h>
#include <iostream>
#define GLFW_ONKEYUP 3
class Keyboard
{
private:
    static int keyToggle[]; //true means the key is pressed
    static bool consumed;
    friend class Window;
public:
    static void glfwKeyboardCallback(GLFWwindow* window, int key, int scancode,
                                     int action, int mods)
    {
        consumed = (bool)TwEventKeyGLFW3(window,key,scancode,action,mods);

        if(!consumed)
        {
            if (keyToggle[key] != GLFW_RELEASE && action == GLFW_RELEASE) {
                action = GLFW_ONKEYUP;
                //std::cout << "key " << key << " is being released once" << std::endl;
            }
        }
        keyToggle[key] = action;
    }

    bool keyPressed(int key)
    {
        int result = keyToggle[key];
        return result != GLFW_RELEASE && result != GLFW_ONKEYUP;
    }

    bool keySinglePressed(int key)
    {
        int result = keyToggle[key];
        if(result == GLFW_ONKEYUP)
            keyToggle[key] = GLFW_RELEASE;
        return result == GLFW_ONKEYUP;
    }



};
#endif //TESTPROJECT2_KEYBOARD_HPP
