//
// Created by lejonmcgowan on 8/20/15.
//

#ifndef TESTPROJECT2_CAMERA_H
#define TESTPROJECT2_CAMERA_H

#include "Transform.h"
#include "utils/WindowContexts.h"

class Camera: public Transform
{
private:
    glm::vec2 pitch_limits, yaw_limits, roll_limits;
    bool pitchFlag = true, yawFlag, rollFlag;

    glm::mat4 viewMatrix, perspectiveMatrix;
    bool updateViewTransform = true, updatePerspectiveTransform = true;

    float fov =  glm::radians(45.0f), nearView = 0.1f, farView = 100.f;
    glm::vec3 worldUp = glm::vec3(0.0f,1.0f, 0.0f);
    glm::vec3 rightBasis, upBasis, frontBasis;

    float clamp(float value, float minValue, float maxValue)
    {
        std::cout << "clamping " << glm::degrees(value) <<  " in range [" << glm::degrees(minValue) << "," << glm::degrees(maxValue) << "]" << std::endl;
        return std::min(std::max(value,minValue), maxValue);
    }

public:
    Camera()
    {
        translateTo(glm::vec3(0.0f,0.0f,3.0f));
        rotateTo(glm::vec3(glm::radians(-90.f),0.0f,0.0f));
        pitch_limits = glm::vec2(glm::radians(-85.0f),glm::radians(85.0f));
    }

    void enablePitchLimits(bool enabled){pitchFlag = enabled;}
    void enableYawLimits(bool enabled){yawFlag = enabled;}
    void enableRollLimits(bool enabled){rollFlag = enabled;}

    void setPitchLimits(glm::vec2 limits)
    {
        pitch_limits = limits;
    }
    void setPitchLimits(float limitMin, float limitMax)
    {
        pitch_limits.x = limitMin;
        pitch_limits.y = limitMax;
    }
    void setYawLimits(glm::vec2 limits)
    {
        yaw_limits = limits;
    }
    void setYawLimits(float limitMin, float limitMax)
    {
        yaw_limits.x = limitMin;
        yaw_limits.y = limitMax;
    }
    void setRollimits(glm::vec2 limits)
    {
        roll_limits = limits;
    }
    void setRollLimits(float limitMin, float limitMax)
    {
        roll_limits.x = limitMin;
        roll_limits.y = limitMax;
    }

    glm::mat4& getViewMatrix()
    {
        if(updateViewTransform)
        {
            //Just as a reminder: rotation.x,y, and z = yaw, pitch, and roll
            frontBasis.x = cos(rotation.y) * cos(rotation.x);
            frontBasis.y = sin(rotation.y);
            frontBasis.z = cos(rotation.y) * sin(rotation.x);

            //update the basis vectors for camera orientation
            frontBasis = glm::normalize(frontBasis);
            rightBasis = glm::normalize(glm::cross(frontBasis,worldUp));
            upBasis = glm::normalize(glm::cross(rightBasis, frontBasis));

            viewMatrix = glm::lookAt(translation, translation + frontBasis, upBasis);
            updateViewTransform = false;
        }

        return viewMatrix;
    }

    glm::mat4 getPerspectiveMatrix()
    {
        if(updatePerspectiveTransform)
        {
            perspectiveMatrix = glm::perspective(fov,WindowContexts::WINDOW_WIDTH / (float)WindowContexts::WINDOW_HEIGHT, nearView, farView);
            //std::cout << glm::degrees(fov) << std::endl;
            updatePerspectiveTransform = false;
        }

        return perspectiveMatrix;
    }

    void translateBy(glm::vec3 factor)
    {
        Transform::translateBy(factor);
        updateViewTransform = true;
    }

    void translateTo(glm::vec3 translation)
    {
        Transform::translateTo(translation);
        updateViewTransform = true;
    }

    void rotateTo(glm::vec3 rotation)
    {
        Transform::rotateTo(rotation);
        updateViewTransform = true;

        if(yawFlag)
            rotation.x = clamp(rotation.x,yaw_limits.x,yaw_limits.y);
        if(pitchFlag)
            rotation.y = clamp(rotation.y,pitch_limits.x,pitch_limits.y);
        if(pitchFlag)
            rotation.z = clamp(rotation.z,roll_limits.x,roll_limits.y);
    }
    void rotateBy(glm::vec3 rotation)
    {
        Transform::rotateBy(rotation);
        updateViewTransform = true;

        if(yawFlag)
            rotation.x = clamp(rotation.x,yaw_limits.x,yaw_limits.y);
        if(pitchFlag) {
            std::cout << glm::degrees(rotation.y) << std::endl;
            rotation.y = clamp(rotation.y, pitch_limits.x, pitch_limits.y);
            std::cout << glm::degrees(rotation.y) << std::endl << std::endl;
        }
        if(pitchFlag)
            rotation.z = clamp(rotation.z,roll_limits.x,roll_limits.y);
    }

    void forwardBy(float sensitivity) //the direstion you are facing is positive
    {
        translateBy(frontBasis * sensitivity);
    }

    void strafeBy(float sensitivity) //in this case, right is positive
    {
        translateBy(rightBasis * sensitivity);
    }

    void changeFOVBy(float factor)
    {
        fov += factor;
        updatePerspectiveTransform = true;
    }
    //convienience methods for use in scenes
    static void WASDMove(Camera& camera, Keyboard& keyboard, float sensitivity)
    {
        if(keyboard.keyPressed(GLFW_KEY_W))
            camera.forwardBy(sensitivity);
        if(keyboard.keyPressed(GLFW_KEY_A))
            camera.strafeBy(-sensitivity);
        if(keyboard.keyPressed(GLFW_KEY_S))
            camera.forwardBy(-sensitivity);
        if(keyboard.keyPressed(GLFW_KEY_D))
            camera.strafeBy(sensitivity);
    }

    static void WASDLook(Camera& camera, Mouse& mouse, float sensitivity)
    {
        glm::vec3 offsets = glm::vec3(mouse.getMouseOffset() * sensitivity, 0.0f);

        camera.rotateBy(offsets);
    }

    static void FOVScroll(Camera& camera, Mouse& mouse, float sensitivity)
    {
        glm::vec2 offsets = mouse.getScrollOffset();

        camera.changeFOVBy(offsets.y * sensitivity);
    }
};
#endif //TESTPROJECT2_CAMERA_H
