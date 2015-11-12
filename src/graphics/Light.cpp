//
// Created by lejonmcgowan on 10/23/15.
//

#include "Light.h"

const static float Quadratic_Attenuation = 75.0f;
const static float Linear_Attenuation = 4.5;
const static float Constant_Attenuation = 1.0f;
const static float range = 100.0f;

int Light::spotID = 0,Light::dirID = 0,Light::pointID = 0;

void Light::setLightRange()
{
    attenuation = glm::vec3(range * range / Quadratic_Attenuation,
                            range / Linear_Attenuation,
                            Constant_Attenuation);
}
//direction light constructor
Light::Light(LightType lightType, glm::vec3 direction):lightType(lightType),
                                                       intensity(1.0f),
                                                       direction(direction),
                                                       id(dirID++)
{
    ambient = glm::vec3(1.0f,1.0f,1.0f);
    diffuse = glm::vec3(1.0f,1.0f,1.0f);
    specular = glm::vec3(1.0f,1.0f,1.0f);

}
//point light constructor
Light::Light(LightType lightType, float intensity, glm::vec3 position):
        lightType(lightType),
        intensity(intensity),
        position(position),
        id(pointID++)
{
    setLightRange();

    ambient = glm::vec3(1.0f,1.0f,1.0f);
    diffuse = glm::vec3(1.0f,1.0f,1.0f);
    specular = glm::vec3(1.0f,1.0f,1.0f);

}
//spot light constructor
Light::Light(LightType lightType, float intensity, float innerCutoffAngle, float outerCutoffAngle):
lightType(lightType),
intensity(intensity),
innerCutoffAngle(innerCutoffAngle),
outerCutoffAngle(outerCutoffAngle),
id(spotID++)
{
    setLightRange();

    ambient = glm::vec3(1.0f,1.0f,1.0f);
    diffuse = glm::vec3(1.0f,1.0f,1.0f);
    specular = glm::vec3(1.0f,1.0f,1.0f);

}

Light::~Light()
{
    switch(lightType)
    {
        case Directional: dirID--;
            break;
        case Point: pointID--;
            break;
        case Spot: spotID--;
            break;
    }
}
