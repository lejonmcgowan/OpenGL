//
// Created by lejonmcgowan on 8/20/15.
//

#ifndef TESTPROJECT2_CAMERA_H
#define TESTPROJECT2_CAMERA_H

#include "Transform.h"
#include "../utils/WindowContexts.h"

class Camera: public Transform
{
private:
    glm::vec2 pitch_limits, yaw_limits, roll_limits;
    bool pitchFlag, yawFlag, rollFlag;

    glm::mat4 viewMatrix, perspectiveMatrix;
    bool updateViewTransform = true, updatePerspectiveTransform = true;

    float fov =  glm::radians(45.0f), nearView = 0.1f, farView = 100.f;
    glm::vec3 worldUp = glm::vec3(0.0f,1.0f, 0.0f);
    glm::vec3 rightBasis, upBasis, frontBasis;

    inline float clamp(float value, float minValue, float maxValue) { return std::min(std::max(value,minValue), maxValue);}

public:
    Camera()
    {
        translateTo(glm::vec3(0.0f,0.0f,-3.0f));
        rotateTo(glm::vec3(glm::radians(90.f),0.0f,0.0f));
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

        if(pitchFlag)
            rotation.x = clamp(rotation.x,pitch_limits.x,pitch_limits.y);
        if(yawFlag)
            rotation.y = clamp(rotation.y,yaw_limits.x,yaw_limits.y);
        if(pitchFlag)
            rotation.z = clamp(rotation.z,roll_limits.x,roll_limits.y);
    }
    void rotateBy(glm::vec3 rotation)
    {
        Transform::rotateBy(rotation);
        updateViewTransform = true;

        if(pitchFlag)
            rotation.x = clamp(rotation.x,pitch_limits.x,pitch_limits.y);
        if(yawFlag)
            rotation.y = clamp(rotation.y,yaw_limits.x,yaw_limits.y);
        if(pitchFlag)
            rotation.z = clamp(rotation.z,roll_limits.x,roll_limits.y);
    }
};
#endif //TESTPROJECT2_CAMERA_H
