//
// Created by lejonmcgowan on 11/2/15.
//

#ifndef TESTPROJECT2_LIGHTHELPER_H
#define TESTPROJECT2_LIGHTHELPER_H

#include <src/graphics/Light.h>
#include <src/graphics/materials/PhongMaterial.h>

class LightHelper
{
    static void setLightColorFromMaterial(Light& light, PhongMaterial& material);
};

#endif //TESTPROJECT2_LIGHTHELPER_H
