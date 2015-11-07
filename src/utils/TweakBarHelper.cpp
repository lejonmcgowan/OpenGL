//
// Created by lejonmcgowan on 11/2/15.
//
#include "TweakBarHelper.h"

void addPointLight(TwBar* bar, Light& light, std::string name = "")
{
    static bool defined = false;
    static TwType TW_TYPE_LIGHT_POINT;
    if(!defined)
    {
        //setup TwStruct for Material
        TwStructMember transformMembers[] = // array used to describe tweakable variables of the Light structure
                {
                        {"Intensity", TW_TYPE_FLOAT, 7 * sizeof(glm::vec3) + 3 * sizeof(float), " "},
                        {"Position", TW_TYPE_DIR3F,   5 * sizeof(glm::vec3), " "},
                        {"Ambient",  TW_TYPE_COLOR3F, 0 * sizeof(glm::vec3), " "},
                        {"Diffuse",  TW_TYPE_COLOR3F, 1 * sizeof(glm::vec3), " "},
                        {"Specular", TW_TYPE_COLOR3F, 2 * sizeof(glm::vec3), " "},
                        {"Contributions",  TW_TYPE_DIR3F, 3 * sizeof(glm::vec3), " "},
                        {"Intensity",  TW_TYPE_FLOAT, 7 * sizeof(glm::vec3), " "},
                };
        // create a new TwType associated to the struct defined by the lightMembers array
        TW_TYPE_LIGHT_POINT = TwDefineStruct("Point Light", transformMembers, 3, 3 * sizeof(glm::vec3),
                                           NULL, NULL);
        defined = true;
    }

    static int numPointLights = 0;
    numPointLights++;
    if(name.empty())
        name = "Point Light " + std::to_string(numPointLights);
    TwAddVarRW(bar,name.c_str(),TW_TYPE_LIGHT_POINT,&light," group='Lights' ");
}

void addSpotLight(TwBar* bar, Light& light, std::string name = "")
{
    static bool defined = false;
    static TwType TW_TYPE_LIGHT_DIRECTION;
    if(!defined)
    {
        //setup TwStruct for Material
        TwStructMember transformMembers[] = // array used to describe tweakable variables of the Light structure
                {
                        {"Intensity", TW_TYPE_FLOAT, 7 * sizeof(glm::vec3) + 3 * sizeof(float), " "},
                        {"Position", TW_TYPE_DIR3F,  4 * sizeof(glm::vec3), " "},
                        {"Ambient",  TW_TYPE_COLOR3F, 0 * sizeof(glm::vec3), " "},
                        {"Diffuse",  TW_TYPE_COLOR3F, 1 * sizeof(glm::vec3), " "},
                        {"Specular", TW_TYPE_COLOR3F, 2 * sizeof(glm::vec3), " "},
                        {"Contributions",  TW_TYPE_DIR3F, 3 * sizeof(glm::vec3), " "},
                        {"Intensity",  TW_TYPE_FLOAT, 7 * sizeof(glm::vec3), " "},
                        {"Inner Cutoff",  TW_TYPE_FLOAT, 7 * sizeof(glm::vec3) + 1 * sizeof(float), " "},
                        {"Outer Cutoff",  TW_TYPE_FLOAT, 7 * sizeof(glm::vec3) + 2 * sizeof(float), " "},
                        {"Smooth Edges", TW_TYPE_BOOLCPP,7 * sizeof(glm::vec3) + 3 * sizeof(float), " "}
                };
        // create a new TwType associated to the struct defined by the lightMembers array
        TW_TYPE_LIGHT_DIRECTION = TwDefineStruct("Direction Light", transformMembers, 3, 3 * sizeof(glm::vec3),
                                                 NULL, NULL);
        defined = true;
    }

    static int numPointLights = 0;
    numPointLights++;
    if(name.empty())
        name = "Point Light " + std::to_string(numPointLights);
    TwAddVarRW(bar, name.c_str(), TW_TYPE_LIGHT_DIRECTION, &light, " group='Lights' ");
}

void addDirectionLight(TwBar* bar, Light& light, std::string name = "")
{
    static bool defined = false;
    static TwType TW_TYPE_LIGHT_POINT_SPOT;
    if(!defined)
    {
        //setup TwStruct for Material
        TwStructMember transformMembers[] = // array used to describe tweakable variables of the Light structure
                {
                        {"Intensity", TW_TYPE_FLOAT, 7 * sizeof(glm::vec3) + 3 * sizeof(float), " "},
                        {"Direction", TW_TYPE_DIR3F,  4 * sizeof(glm::vec3), " "},
                        {"Ambient",  TW_TYPE_COLOR3F, 0 * sizeof(glm::vec3), " "},
                        {"Diffuse",  TW_TYPE_COLOR3F, 1 * sizeof(glm::vec3), " "},
                        {"Specular", TW_TYPE_COLOR3F, 2 * sizeof(glm::vec3), " "},
                        {"Contributions",  TW_TYPE_DIR3F, 3 * sizeof(glm::vec3), " "},
                };
        // create a new TwType associated to the struct defined by the lightMembers array
        TW_TYPE_LIGHT_POINT_SPOT = TwDefineStruct("Spot Light", transformMembers, 3, 3 * sizeof(glm::vec3),
                                                  NULL, NULL);
        defined = true;
    }

    static int numPointLights = 0;
    numPointLights++;
    if(name.empty())
        name = "Point Light " + std::to_string(numPointLights);
    TwAddVarRW(bar, name.c_str(), TW_TYPE_LIGHT_POINT_SPOT, &light, " group='Lights' ");
}

void TweakBarHelper::addMaterial(TwBar* bar, PhongMaterial& material, std::string name)
{
    static bool defined = false;
    static TwType TW_TYPE_MATERIAL;
    if(!defined)
    {
        //setup TwStruct for Material
        TwStructMember materialMembers[] = // array used to describe tweakable variables of the Light structure
                {
                        {"Ambient",     TW_TYPE_COLOR3F, 0 * sizeof(glm::vec3), " "},
                        {"DIffuse",     TW_TYPE_COLOR3F, 1 * sizeof(glm::vec3), " "},
                        {"Specular",    TW_TYPE_COLOR3F, 2 * sizeof(glm::vec3), " "},
                        {"specularExp", TW_TYPE_FLOAT,   3 * sizeof(glm::vec3),     " min=0 max=256 step= 2 help='shininess' "}
                };
        // create a new TwType associated to the struct defined by the lightMembers array
        TW_TYPE_MATERIAL = TwDefineStruct("Material", materialMembers, 4, 3 * sizeof(glm::vec3) + sizeof(float),
                                          NULL, NULL);
        defined = true;
    }

    static int numMaterials = 0;
    numMaterials++;
    if(name.empty())
        name = "Material " + std::to_string(numMaterials);
    //plz work...
    TwAddVarRW(bar,name.c_str(),TW_TYPE_MATERIAL,&material," group='Materials' ");
}

void TweakBarHelper::addTransform(TwBar* bar, Transform& transform, std::string name)
{
    static bool defined = false;
    static TwType TW_TYPE_TRANSFORM;
    if(!defined)
    {
        //setup TwStruct for Material
        TwStructMember transformMembers[] = // array used to describe tweakable variables of the Light structure
                {
                        {"Translation",  TW_TYPE_DIR3F, 0 * sizeof(glm::vec3), " "},
                        {"Rotation",     TW_TYPE_DIR3F, 1 * sizeof(glm::vec3), " "},
                        {"Scale",        TW_TYPE_DIR3F, 2 * sizeof(glm::vec3), " "}
                };
        // create a new TwType associated to the struct defined by the lightMembers array
        TW_TYPE_TRANSFORM = TwDefineStruct("Transform", transformMembers, 3, 3 * sizeof(glm::vec3),
                                           NULL, NULL);
        defined = true;
    }

    static int numTransforms = 0;
    numTransforms++;
    if(name.empty())
        name = "Transform " + std::to_string(numTransforms);
    //plz work...
    TwAddVarRW(bar,name.c_str(),TW_TYPE_TRANSFORM,&transform," group='Transforms' ");
}

void TweakBarHelper::addLight(TwBar *bar, Light &light, std::string name)
{
    switch(light.getLightType())
    {
        case LightType ::Spot:
            addSpotLight(bar,light,name);
            break;
        case LightType::Point:
            addPointLight(bar,light,name);
            break;
        case LightType::Directional:
            addDirectionLight(bar,light,name);
    }
}
