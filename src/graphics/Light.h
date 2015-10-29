//
// Created by lejonmcgowan on 10/23/15.
//

#ifndef TESTPROJECT2_LIGHT_H
#define TESTPROJECT2_LIGHT_H

#include <glm/detail/type_vec3.hpp>
#include "shader.h"
#include "shaderManager.h"

enum LightType
{
    Directional,
    Point,
    Spotlight
};

class Light
{
private:
    LightType lightType;
//color properties of light
    glm::vec3 ambient,diffuse,specular;
    float intensity;
    //for non-point lights
    glm::vec3 direction;
    /*inverse quadratic attenuation. will be calculated based on values from OGRE3D's Wiki
      values are stored as (quadric,linear,constant)*/
    glm::vec3 attenuation;
    float range;
    //for spotlights
    float innerCutoffAngle, outerCutoffAngle;
    bool smoothEdges;
public:
    Light(LightType lightType, float range, float innerCutoffAngle = 60, float outerCUtoffAngle = 65);
    Light(LightType lightType, float range, glm::vec3 direction);
    void makeLightStructUniform(Shader& shader, std::string structName = "light", int index = -1);
    void makeLightStructUniform(ShaderManager& shader, std::string structName = "light", int index = -1);

    //for attenuation
    void setLightRange(float range);
    //getters/setters
    const glm::vec3 &getAmbient() const
    {
        return ambient;
    }
    void setAmbient(const glm::vec3 &ambient)
    {
        Light::ambient = ambient;
    }
    const glm::vec3 &getDiffuse() const
    {
        return diffuse;
    }
    void setDiffuse(const glm::vec3 &diffuse)
    {
        Light::diffuse = diffuse;
    }
    const glm::vec3 &getSpecular() const
    {
        return specular;
    }
    void setSpecular(const glm::vec3 &specular)
    {
        Light::specular = specular;
    }
    float getIntensity() const
    {
        return intensity;
    }
    void setIntensity(float intensity)
    {
        Light::intensity = intensity;
    }
    const glm::vec3 &getDirection() const
    {
        return direction;
    }
    void setDirection(const glm::vec3 &direction)
    {
        Light::direction = direction;
    }
    float getOuterCutoff() const
    {
        return outerCutoffAngle;
    }
    void setHardCutoff(float outerCutoff)
    {
        this->outerCutoffAngle = outerCutoff;
    }
    float getInnerCutoff() const
    {
        return innerCutoffAngle;
    }
    void setInnerCutoff(float softCutoff)
    {
        Light::innerCutoffAngle = softCutoff;
    }
    bool isSmoothEdges() const
    {
        return smoothEdges;
    }
    void setSmoothEdges(bool smoothEdges)
    {
        Light::smoothEdges = smoothEdges;
    }
};

#endif //TESTPROJECT2_LIGHT_H
