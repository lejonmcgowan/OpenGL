//
// Created by lejonmcgowan on 8/20/15.
//

#ifndef TESTPROJECT2_CAMERA_H
#define TESTPROJECT2_CAMERA_H

#include "Transform.h"

class Camera: public Transform
{
private:
    glm::vec2 pitch_limits, yaw_limits, roll_limits;
    bool pitchFlag, yawFlag, rollFlag;
    float fov;
    inline float clamp(float value, float min, float max) { return min(max(value,min), max);}
public:
    Camera(){}

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

    void rotateTo(glm::vec3 rotation) override
    {
        Transform::rotateTo(rotation);

        if(pitch_limits)
            rotation.x = clamp(rotation.x,pitch_limits.x,pitch_limits.y);
        if(yaw_limits)
            rotation.y = clamp(rotation.y,yaw_limits.x,yaw_limits.y);
        if(pitch_limits)
            rotation.z = clamp(rotation.z,roll_limits.x,roll_limits.y);
    }
};
#endif //TESTPROJECT2_CAMERA_H
