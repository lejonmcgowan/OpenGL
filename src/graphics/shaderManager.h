//
// Created by lejonmcgowan on 6/27/15.
//

#ifndef TESTPROJECT2_SHADERMANAGER_H
#define TESTPROJECT2_SHADERMANAGER_H

#include <map>
#include <algorithm>
#include "shader.h"



#define uppercase(str) std::transform(str.begin(), str.end(),str.begin(), ::toupper)

class ShaderManager
{
private:
    std::map<std::string, Shader> shaders;
    Shader currentShader;
public:
    void addShader(std::string name,Shader& shader)
    {
        uppercase(name);
        shader.setName(name);
        shaders[name] = shader;
    }
    void setShader(std::string shaderKey)
    {
        uppercase(shaderKey);
        if(shaders.count(shaderKey) == 0)
            std::cout << "No shader of name" << shaderKey << std::endl;
        else
            currentShader = shaders[shaderKey];
    }
    void bind()
    {
        currentShader.bind();
    }
    void unbind()
    {
        currentShader.unbind();
    }
    std::string getCurrentShaderName()
    {
        return currentShader.getName();
    }

    void setUniform(std::string uniformName, int data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }
    void setUniform(std::string uniformName, float data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }

    void setUniform(std::string uniformName, glm::vec2 data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }
    void setUniform(std::string uniformName, glm::vec3 data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }
    void setUniform(std::string uniformName, glm::vec4 data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }

    void setUniform(std::string uniformName, glm::mat2 data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }
    void setUniform(std::string uniformName, glm::mat3 data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }
    void setUniform(std::string uniformName, glm::mat4 data, std::string shaderName = "")
    {
        if(shaderName.empty())
            shaderName =  currentShader.getName();

        shaders[shaderName].setUniform(uniformName,data);
    }

};


#endif //TESTPROJECT2_SHADERMANAGER_H
