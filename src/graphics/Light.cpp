//
// Created by lejonmcgowan on 10/23/15.
//

#include "Light.h"
const static float Quadratic_Attenuation = 75.0f;
const static float Linear_Attenuation = 4.5;
const static float Constant_Attenuation = 1.0f;

void Light::setLightRange(float range)
{
    this->range = range;
    attenuation = glm::vec3(range * range / Quadratic_Attenuation,
                            range / Linear_Attenuation,
                            Constant_Attenuation);
}

Light::Light(LightType lightType, float range, float innerCutoffAngle, float outerCutoffAngle):
lightType(lightType),
innerCutoffAngle(innerCutoffAngle),
outerCutoffAngle(outerCutoffAngle)
{
    setLightRange(range);
}

Light::Light(LightType lightType, float range, glm::vec3 direction):
        lightType(lightType),
        direction(direction)
{
    setLightRange(range);
}

void Light::makeLightStructUniform(Shader &shader, std::string structName, int index)
{
    shader.setStructUniform(structName,"ambient",ambient);
    shader.setStructUniform(structName,"diffuse",diffuse);
    shader.setStructUniform(structName,"specular",specular);
}

void Light::makeLightStructUniform(ShaderManager &shader, std::string structName, int index)
{

}
