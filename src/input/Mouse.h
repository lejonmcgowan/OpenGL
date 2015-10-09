//
// Created by lejonmcgowan on 8/22/15.
//

#ifndef TESTPROJECT2_MOUSE_H
#define TESTPROJECT2_MOUSE_H


#include <GLFW/glfw3.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <iostream>

class Mouse
{
private:
    static int mouseToggles[GLFW_MOUSE_BUTTON_LAST];
    static glm::vec2 currentCursorPosition, lastCursorPosition, cursorOffset;
    static glm::vec2 currentScrollPosition, lastScrollPosition, scrollOffset;
    static bool initialized;
    static int lastButton, lastAction, lastMods;
public:
    //static callbacks
    static void glfwMouseCursorCallback(GLFWwindow* window, double xPos, double yPos)
    {
        if(!initialized)
        {
            lastCursorPosition = glm::vec2(xPos, yPos);
            currentCursorPosition = glm::vec2(lastCursorPosition);
            initialized = true;
        }

      //  updateCursor(glm::vec2(xPos,yPos));
    }

    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if(action == GLFW_PRESS)
        {
            if (mouseToggles[button] == GLFW_PRESS)
            {
                mouseToggles[button] = GLFW_REPEAT;
                lastButton = GLFW_KEY_UNKNOWN;
            }
            else
            {
                mouseToggles[button] = GLFW_PRESS;
                lastButton = mouseToggles[button];
            }
        }
        else if(action == GLFW_RELEASE)
            mouseToggles[button] = false;

        lastAction = action;
        lastMods = mods;
    }

    static int getLastButton()
    {
        return lastButton;
    }

    static int getLastAction()
    {
        return lastAction;
    }

    static int getLastMods()
    {
        return lastMods;
    }

    static void glfwScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        lastScrollPosition = currentScrollPosition;

        currentScrollPosition.x = xOffset;
        currentScrollPosition.y = yOffset;

        scrollOffset = currentScrollPosition - lastScrollPosition;
    }

    //query from the events polled
    bool getMouseButtonPressed(int button)
    {
        return mouseToggles[button] == GLFW_PRESS;
    }

    bool getMouseButtonHeld(int button)
    {
        return mouseToggles[button] == GLFW_REPEAT;
    }

    glm::vec2 getMouseOffset()
    {
        return cursorOffset;
    }

    glm::vec2 getCursorPos()
    {
        return currentCursorPosition;
    }

    glm::vec2 getScrollOffset()
    {
        return scrollOffset;
    }

    static void updateCursor(glm::vec2 currentPos)
    {
        lastCursorPosition = currentCursorPosition;

        currentCursorPosition = currentPos;

        cursorOffset = currentCursorPosition - lastCursorPosition;
        cursorOffset.y *= -1;
    }
};


#endif //TESTPROJECT2_MOUSE_H
