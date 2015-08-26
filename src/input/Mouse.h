//
// Created by lejonmcgowan on 8/22/15.
//

#ifndef TESTPROJECT2_MOUSE_H
#define TESTPROJECT2_MOUSE_H


#include <GLFW/glfw3.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>

class Mouse
{
private:
    static bool mouseToggles[GLFW_MOUSE_BUTTON_LAST];
    static glm::vec2 currentCursorPosition, lastCursorPosition;
    static glm::vec2 currentScrollOffset;
    static bool initialized;
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

        lastCursorPosition.x = currentCursorPosition.x;
        lastCursorPosition.y = currentCursorPosition.y;

        currentCursorPosition.x = (float)xPos;
        currentCursorPosition.y = (float)yPos;
    }
    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if(action == GLFW_PRESS)
            mouseToggles[button] = true;
        else if(action == GLFW_RELEASE)
            mouseToggles[button] = false;
    }

    static void glfwScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        currentScrollOffset.x = xOffset;
        currentScrollOffset.y = yOffset;
    }

    //query from the events polled
    bool getMouseButtonPressed(int button)
    {
        return mouseToggles[button];
    }

    glm::vec2 getMouseOffset()
    {
        return currentCursorPosition - lastCursorPosition;
    }

    glm::vec2& getScrollOffset()
    {
        return currentScrollOffset;
    }

};


#endif //TESTPROJECT2_MOUSE_H
