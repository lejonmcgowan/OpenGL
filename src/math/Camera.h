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
    float fov =  glm::radians(45.0f), nearView = 0.1f, farView = 100.f;
    glm::vec3 frontBasis = glm::vec3(0.0f,0.0f,-1.0f), upBasis = glm::vec3(0.0f,1.0f,0.0f);

    inline float clamp(float value, float minValue, float maxValue) { return std::min(std::max(value,minValue), maxValue);}

public:
    Camera()
    {
        translation = glm::vec3(0.0f,0.0f,3.0f);
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

    void rotateTo(glm::vec3 rotation)
    {
        Transform::rotateTo(rotation);

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

        if(pitchFlag)
            rotation.x = clamp(rotation.x,pitch_limits.x,pitch_limits.y);
        if(yawFlag)
            rotation.y = clamp(rotation.y,yaw_limits.x,yaw_limits.y);
        if(pitchFlag)
            rotation.z = clamp(rotation.z,roll_limits.x,roll_limits.y);
    }

    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(translation, translation + frontBasis, upBasis);
    }

    glm::mat4 getPerspectiveMatrix()
    {
        return glm::perspective(fov,WindowContexts::WINDOW_WIDTH / (float)WindowContexts::WINDOW_HEIGHT, nearView, farView);
    }
};
#endif //TESTPROJECT2_CAMERA_H
