//
// Created by lejonmcgowan on 11/2/15.
//

#ifndef TESTPROJECT2_LIGHTHELPER_H
#define TESTPROJECT2_LIGHTHELPER_H

#include <src/graphics/Light.h>
#include <src/graphics/materials/PhongMaterial.h>
#include <glm/detail/type_vec3.hpp>
#include "graphics/shader.h"
#include "graphics/shaderManager.h"
#include "graphics/Light.h"

struct LightHelper
{
    static void setLightColorFromMaterial(Light& light, PhongMaterial& material);

    static void makeLightStructUniform(Light& light, Shader& shader, std::string structName = "light", int index = -1);

    static void makeLightStructUniform(Light& light, ShaderManager& shader, std::string structName = "light", int index = -1);
};

#endif //TESTPROJECT2_LIGHTHELPER_H
