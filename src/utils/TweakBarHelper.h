//
// Created by lejonmcgowan on 11/2/15.
//

#ifndef TESTPROJECT2_TWEAKBARHELPER_H
#define TESTPROJECT2_TWEAKBARHELPER_H

#include "graphics/Light.h"
#include "graphics/materials/PhongMaterial.h"
#include "math/Transform.h"
#include "ext/include/AntTweakBar.h"

class TweakBarHelper
{
private:
public:
    static void addMaterial(TwBar* bar, PhongMaterial& material, std::string name = "");
    static void addTransform(TwBar* bar, Transform& transform, std::string name = "");
    static void addLight(TwBar* bar,Light& light, std::string name = "");
};

#endif //TESTPROJECT2_TWEAKBARHELPER_H
