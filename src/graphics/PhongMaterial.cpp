//
// Created by lejonmcgowan on 10/20/15.
//

#include "PhongMaterial.h"

PhongMaterial::PhongMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specularExp):
ambient(ambient),
diffuse(diffuse),
specular(specular),
specularExp(specularExp)
{

}

//will be a grey material by default as to differ from the typcical black lighting failure
PhongMaterial::PhongMaterial():
PhongMaterial(glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),32)
{

}

void PhongMaterial::setMaterialUniform(Shader &shader, std::string structName)
{
    shader.setStructUniform(structName,"ambient",ambient * intensities[0]);
    shader.setStructUniform(structName,"diffuse",diffuse * intensities[1]);
    shader.setStructUniform(structName,"specular",specular * intensities[2]);
    shader.setStructUniform(structName,"specularExp",specularExp);
}

void PhongMaterial::setMaterialUniform(ShaderManager &shader, std::string structName)
{
    shader.setStructUniform(structName,"ambient",ambient * intensities[0]);
    shader.setStructUniform(structName,"diffuse",diffuse * intensities[1]);
    shader.setStructUniform(structName,"specular",specular * intensities[2]);
    shader.setStructUniform(structName,"specularExp",specularExp);
}

//preset Material colors. from http://devernay.free.fr/cours/opengl/materials.html
const PhongMaterial PhongMaterialFactory::JADE(glm::vec3(0.135f,0.225f,0.1575f),
                                               glm::vec3(0.54f,0.89f,0.63f),
                                               glm::vec3(0.3162f,0.3162f,0.3162f),
                                                12.8f);
const PhongMaterial PhongMaterialFactory::SAPPHIRE(glm::vec3(0.1745f,0.01175f,0.01175f),
                                                   glm::vec3(0.6142f,0.4136f,0.4136f),
                                                   glm::vec3(0.7281f,0.6270f,0.6370f),
                                                   76.8);

const PhongMaterial PhongMaterialFactory::WHITE(glm::vec3(1.0f,1.0f,1.0f),
                                            glm::vec3(1.0f,1.0f,1.0f),
                                            glm::vec3(1.0f,1.0f,1.0f));
