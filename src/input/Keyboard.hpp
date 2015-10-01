//
// Created by lejonmcgowan on 8/16/15.
//

#ifndef TESTPROJECT2_KEYBOARD_HPP
#define TESTPROJECT2_KEYBOARD_HPP

#include <GLFW/glfw3.h>

class Keyboard {
private:
    static bool keyToggle[]; //true means the key is pressed
    static int lastAction;
    static int lastKeyPressed; //key unknown
    static int lastMods;
    static int lastScancode;
public:
    static void glfwKeyboardCallback(GLFWwindow* window, int key, int scancode,
                                     int action, int mods) {
        switch (action)
        {
            case GLFW_PRESS:
                Keyboard::keyToggle[key] = true;
                lastKeyPressed = key;
                break;
            case GLFW_RELEASE:
                Keyboard::keyToggle[key] = false;
                lastKeyPressed = GLFW_KEY_UNKNOWN;
                break;
        }
        lastAction = action;
        lastMods = mods;
        lastScancode = scancode;
    }

    bool keyPressed(int key)
    {
        bool result = keyToggle[key];
        keyToggle[key] = false; //will eliminate key repetition issue?
        return result;
    }

    int getLastAction(){return lastAction;}
    int getLastKeyPressed(){return lastKeyPressed;}
    int getLastMods(){return lastMods;}
    int getLastScancode(){return lastScancode;}

};
#endif //TESTPROJECT2_KEYBOARD_HPP
