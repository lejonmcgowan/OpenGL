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
