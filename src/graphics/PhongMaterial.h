//
// Created by lejonmcgowan on 10/20/15.
//

#ifndef TESTPROJECT2_MATERIAL_H
#define TESTPROJECT2_MATERIAL_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include "shader.h"

class PhongMaterial
{
private:
//3 material colors for blinn-phong
    glm::vec3 ambient, diffuse, specular;
private:
    float specularExp;
    /*how much ambient,diffuse, and specular properties, respectively,
      contrbute to the material color*/
    glm::vec3 contributions = glm::vec3(1.0f,1.0f,1.0f);

public:
    PhongMaterial();
    PhongMaterial(glm::vec3 ambient,glm::vec3 diffuse, glm::vec3 specular, float specularExp = 32);

    /**
     * set a shader unifoirm for a struct with the name structName. will assume the following syntax
     * for declaring the shader struct:
     *
     * struct Material
     * {
     *   vec3 ambient;
     *   vec3 diffuse;
     *   vec3 specular;
     *   float specularExp
     * }
     */
    void setMaterialUniform(Shader& shader, std::string structName = "Material");

    //typical querying methods
    const glm::vec3 &getDiffuse() const
    {
        return diffuse;
    }
    void setDiffuse(const glm::vec3 diffuse)
    {
        PhongMaterial::diffuse = diffuse;
    }
    const glm::vec3 &getAmbient() const
    {
        return ambient;
    }
    void setAmbient(const glm::vec3 ambient)
    {
        PhongMaterial::ambient = ambient;
    }
    const glm::vec3 &getSpecular() const
    {
        return specular;
    }
    void setSpecular(const glm::vec3 specular)
    {
        PhongMaterial::specular = specular;
    }
    float getSpecularExp() const
    {
        return specularExp;
    }

    void setSpecularExp(float specularExp)
    {
        PhongMaterial::specularExp = specularExp;
    }
    //some preset materials
public:
    const static PhongMaterial JADE;
    const static PhongMaterial SAPPHIRE;
};

#endif //TESTPROJECT2_MATERIAL_H
