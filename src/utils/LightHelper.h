//
// Created by lejonmcgowan on 11/2/15.
//

#ifndef TESTPROJECT2_LIGHTHELPER_H
#define TESTPROJECT2_LIGHTHELPER_H

#include <src/graphics/materials/PhongMaterial.h>
#include <glm/detail/type_vec3.hpp>
#include "graphics/Shader.h"
#include "graphics/ShaderManager.h"
#include "graphics/Light.h"

struct LightHelper
{
    static void setLightColorFromMaterial(Light& light, PhongMaterial& material);

    static void makeLightStructUniform(Light& light, Shader& shader,bool array, std::string structName = "");

    static void makeLightStructUniform(Light& light, ShaderManager& shader, bool array,std::string structName = "");
};

#endif //TESTPROJECT2_LIGHTHELPER_H
