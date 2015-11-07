//
// Created by lejonmcgowan on 11/2/15.
//
#include "LightHelper.h"

void LightHelper::setLightColorFromMaterial(Light &light, PhongMaterial& &material)
{
    light.setAmbient(material.getAmbient());
    light.setDiffuse(material.getDiffuse());
    light.setSpecular(material.getSpecular());
}

void makeSpotLightStruct(Light& light, Shader& shader,std::string structName, int index)
{
    if(structName.empty())
        structName = "SpotLight";

    shader.setStructUniform(structName,"numLights",Light::spotID);
    shader.setStructUniform(structName, "ambient", light.getAmbient(), index);
    shader.setStructUniform(structName, "diffuse", light.getDiffuse(), index);
    shader.setStructUniform(structName, "specular",light.getSpecular(), index);
    shader.setStructUniform(structName, "intensity",light.getIntensity(), index);

    shader.setStructUniform(structName, "innerCutoff", light.getInnerCutoff(), index);
    shader.setStructUniform(structName, "outerCutoff", light.getOuterCutoff(), index);

}

void makeDirLightStruct(Light& light, Shader& shader,std::string structName, int index)
{
    if(structName.empty())
        structName = "DirLight";

    shader.setStructUniform(structName,"numLights",Light::dirID);
    shader.setStructUniform(structName, "ambient", light.getAmbient(), index);
    shader.setStructUniform(structName, "diffuse", light.getDiffuse(), index);
    shader.setStructUniform(structName, "specular",light.getSpecular(), index);
    shader.setStructUniform(structName, "intensity",light.getIntensity(), index);

    shader.setStructUniform(structName, "direction",light.getDirection(), index);

}

void makePointLightStruct(Light& light, Shader& shader,std::string structName, int index)
{
    if(structName.empty())
        structName = "PointLight";

    shader.setStructUniform(structName,"numLights",Light::pointID);
    shader.setStructUniform(structName, "ambient", light.getAmbient(), index);
    shader.setStructUniform(structName, "diffuse", light.getDiffuse(), index);
    shader.setStructUniform(structName, "specular",light.getSpecular(), index);
    shader.setStructUniform(structName, "intensity",light.getIntensity(), index);

    shader.setStructUniform(structName, "attenuation",light.getAttenuation(), index);

}

void makeSpotLightStruct(Light& light, ShaderManager& shader,std::string structName, int index)
{
    if(structName.empty())
        structName = "SpotLight";

    shader.setStructUniform(structName, "ambient", light.getAmbient(), index);
    shader.setStructUniform(structName, "diffuse", light.getDiffuse(), index);
    shader.setStructUniform(structName, "specular",light.getSpecular(), index);
    shader.setStructUniform(structName, "intensity",light.getIntensity(), index);

    shader.setStructUniform(structName, "innerCutoff", light.getInnerCutoff(), index);
    shader.setStructUniform(structName, "outerCutoff", light.getOuterCutoff(), index);

}

void makeDirLightStruct(Light& light, ShaderManager& shader,std::string structName, int index)
{
    if(structName.empty())
        structName = "DirLight";

    shader.setStructUniform(structName, "ambient", light.getAmbient(), index);
    shader.setStructUniform(structName, "diffuse", light.getDiffuse(), index);
    shader.setStructUniform(structName, "specular",light.getSpecular(), index);
    shader.setStructUniform(structName, "intensity",light.getIntensity(), index);

    shader.setStructUniform(structName, "direction",light.getDirection(), index);

}

void makePointLightStruct(Light& light, ShaderManager& shader,std::string structName, int index)
{
    if(structName.empty())
        structName = "PointLight";

    shader.setStructUniform(structName, "ambient", light.getAmbient(), index);
    shader.setStructUniform(structName, "diffuse", light.getDiffuse(), index);
    shader.setStructUniform(structName, "specular",light.getSpecular(), index);
    shader.setStructUniform(structName, "intensity",light.getIntensity(), index);

    shader.setStructUniform(structName, "attenuation",light.getAttenuation(), index);

}

void LightHelper::makeLightStructUniform(Light& light, Shader &shader, std::string structName, int index)
{
    switch(light.getLightType())
    {
        case Directional:
            makeDirLightStruct(light,shader,structName,index);
            break;
        case Point:
            makePointLightStruct(light,shader,structName,index);
            break;
        case Spot:
            makeSpotLightStruct(light,shader,structName,index);
            break;
    }
}

void LightHelper::makeLightStructUniform(Light& light, ShaderManager &shader, std::string structName, int index)
{
    switch(light.getLightType())
    {
        case Directional:
            makeDirLightStruct(light,shader,structName,index);
            break;
        case Point:
            makePointLightStruct(light,shader,structName,index);
            break;
        case Spot:
            makeSpotLightStruct(light,shader,structName,index);
            break;
    }
}
