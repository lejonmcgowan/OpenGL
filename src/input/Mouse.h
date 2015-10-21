//
// Created by lejonmcgowan on 8/22/15.
//

#ifndef TESTPROJECT2_MOUSE_H
#define TESTPROJECT2_MOUSE_H


#include <GLFW/glfw3.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <iostream>
#include <ext/include/AntTweakBar.h>

class Mouse
{
private:
    static int mouseToggles[GLFW_MOUSE_BUTTON_LAST];
    static glm::vec2 currentCursorPosition, lastCursorPosition, cursorOffset;
    static glm::vec2 currentScrollPosition, lastScrollPosition, scrollOffset;
public:
    //static callbacks
    static void glfwMouseCursorCallback(GLFWwindow* window, double xPos, double yPos)
    {
        TwEventCursorPosGLFW3(window,xPos,yPos);
        updateCursor(glm::vec2(xPos,yPos));
    }

    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        bool consumed = (bool)TwEventMouseButtonGLFW3(window,button,action,mods);
        if(!consumed)
            mouseToggles[button] = action;
    }


    static void glfwScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        bool consumed = (bool)TwEventScrollGLFW3(window,xOffset,yOffset);
        if(!consumed)
            updateScroll(glm::vec2(xOffset,yOffset));
    }

    //query from the events polled
    bool getMouseButtonPressed(int button)
    {
        return mouseToggles[button] != GLFW_RELEASE;
    }

    glm::vec2 getMouseOffset()
    {
        glm::vec2 returnedOffset = cursorOffset;
        updateCursor(currentCursorPosition);
        return returnedOffset;
    }

    glm::vec2 getScrollOffset()
    {
        glm::vec2 returnedOffset = scrollOffset;
        updateScroll(currentScrollPosition);
        return returnedOffset;
    }

    glm::vec2 getCursorPos()
    {
        return currentCursorPosition;
    }

    static void updateCursor(glm::vec2 currentPos)
    {
        lastCursorPosition = currentCursorPosition;

        currentCursorPosition = currentPos;

        cursorOffset = currentCursorPosition - lastCursorPosition;
        cursorOffset.y *= -1;
    }

    static void updateScroll(glm::vec2 offset)
    {
        currentScrollPosition = glm::vec2();
    }
};


#endif //TESTPROJECT2_MOUSE_H
