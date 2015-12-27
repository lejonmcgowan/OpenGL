//
// Created by lejonmcgowan on 6/27/15.
//

#ifndef TESTPROJECT2_SHADERMANAGER_H
#define TESTPROJECT2_SHADERMANAGER_H

#include <map>
#include <algorithm>
#include "Shader.h"



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

    void setUniform(std::string uniformName, int data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }
    void setUniform(std::string uniformName, float data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }

    void setUniform(std::string uniformName, const glm::vec2& data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }
    void setUniform(std::string uniformName, const glm::vec3& data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }
    void setUniform(std::string uniformName, const glm::vec4& data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }

    void setUniform(std::string uniformName, const glm::mat2& data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }
    void setUniform(std::string uniformName, const glm::mat3& data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }
    void setUniform(std::string uniformName, const glm::mat4& data, int index = -1)
    {
        shaders[currentShader.getName()].setUniform(uniformName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, int data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, float data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, const glm::vec2& data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, const glm::vec3& data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, const glm::vec4& data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, const glm::mat2& data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, const glm::mat3& data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStructUniform(std::string structName, std::string attributeName, const glm::mat4& data, int index = -1)
    {
        shaders[currentShader.getName()].setStructUniform(structName,attributeName,data, index);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, int data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data, attributeIndex);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, float data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data,attributeIndex);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, const glm::vec2& data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data, attributeIndex);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, const glm::vec3& data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data, attributeIndex);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, const glm::vec4& data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data, attributeIndex);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, const glm::mat2& data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data, attributeIndex);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, const glm::mat3& data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data, attributeIndex);
    }

    void setStrucArraytUniform(std::string structName, int structIndex, std::string attributeName, const glm::mat4& data, int attributeIndex = -1)
    {
        shaders[currentShader.getName()].setStructArrayUniform(structName,structIndex, attributeName,data, attributeIndex);
    }

};


#endif //TESTPROJECT2_SHADERMANAGER_H
