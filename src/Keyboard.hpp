//
// Created by lejonmcgowan on 8/16/15.
//

#ifndef TESTPROJECT2_KEYBOARD_HPP
#define TESTPROJECT2_KEYBOARD_HPP

#include <GLFW/glfw3.h>

class Keyboard {
public:
    static bool keyToggle[GLFW_KEY_LAST]; //true means the key is pressed

    Keyboard() {
        for (auto& key: Keyboard::keyToggle)
            key = false;
    }

    static void glfwKeyboardCallback(GLFWwindow* window, int key, int scancode,
                                     int action, int mods) {
        switch (action)
        {
            case GLFW_PRESS:
            Keyboard::keyToggle[key] = true;
                break;
            case GLFW_RELEASE:
            Keyboard::keyToggle[key] = false;
                break;
        }
    }

    bool keyPressed(int key) {
        return keyToggle[key];
    }

};
#endif //TESTPROJECT2_KEYBOARD_HPP
