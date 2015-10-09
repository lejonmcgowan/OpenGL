//
// Created by lejonmcgowan on 8/16/15.
//

#ifndef TESTPROJECT2_KEYBOARD_HPP
#define TESTPROJECT2_KEYBOARD_HPP

#include <GLFW/glfw3.h>
#include <valarray>

class Keyboard
{
private:
    static int keyToggle[]; //true means the key is pressed
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
                if(keyToggle[key] == GLFW_PRESS)
                {
                    Keyboard::keyToggle[key] = GLFW_REPEAT;
                    lastKeyPressed = key;
                }
                else
                {
                    Keyboard::keyToggle[key] = GLFW_PRESS;
                    lastKeyPressed = GLFW_KEY_UNKNOWN;
                }
                break;
            case GLFW_RELEASE:
                Keyboard::keyToggle[key] = GLFW_RELEASE;
                lastKeyPressed = GLFW_KEY_UNKNOWN;
                break;
        }
        lastAction = action;
        lastMods = mods;
        lastScancode = scancode;
    }

    bool keyPressed(int key)
    {
        int result = keyToggle[key];
        return result == GLFW_PRESS;
    }

    bool keyHeld(int key)
    {
        int result = keyToggle[key];
        return result == GLFW_RELEASE;
    }

    int getLastAction(){return lastAction;}
    int getLastKeyPressed(){return lastKeyPressed;}
    int getLastMods(){return lastMods;}
    int getLastScancode(){return lastScancode;}

};
#endif //TESTPROJECT2_KEYBOARD_HPP
