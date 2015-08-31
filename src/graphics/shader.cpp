#include "shader.h"
#include "utils/debugGL.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>

#define ERROR_MESSAGE(message, name) std::cout << __FILE__ << " " << __LINE__ << ": " << name << ": " << message << std::endl

bool fileExists(const std::string& fileName)
{
    struct stat info;
    int ret = -1;

    ret = stat(fileName.c_str(), &info);
    return 0 == ret;
}

const std::string Shader::getShaderSource(std::string path)
{
    if( ! fileExists(path) )
    {
        std::string message = "Shader: " + path + " not found.";
        ERROR_MESSAGE(message, name);
        assert(0);
    }

    std::ifstream inFile(path, std::ios::in );
    if( !inFile ) {
        std::string message = "Unable to open: " + path;
        ERROR_MESSAGE(message, name);
        assert(0);
    }

    // Get file contents
    std::stringstream data;
    data << inFile.rdbuf();
    inFile.close();

    const std::string& code = data.str();
    return code;
}
void Shader::checkForCompileErrors(GLuint& handle, GLenum type)
{
    std::string shaderType = type == GL_VERTEX_SHADER ? "VERTEX" : type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "GEOMETRY";
    GLint success;
    GLchar infoLog[512] = "NOTHING";
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(handle, 512, NULL, infoLog);
        std::string message(infoLog);
        message = "ERROR: shader " + shaderType + " failed: " + message;

        ERROR_MESSAGE(message, name);
        assert(0);
    }
}

void Shader::compileShader(std::string path, GLuint& shaderHandle, GLenum shaderType)
{
    assert(!debugGL::checkErrors(__FILE__,__LINE__));
    shaderHandle = glCreateShader(shaderType);
    assert(!debugGL::checkErrors(__FILE__,__LINE__));
    std::string shaderData = getShaderSource(path);
    const char* source = shaderData.c_str();
    glShaderSource(shaderHandle, 1, &source, NULL);
    glCompileShader(shaderHandle);
    checkForCompileErrors(shaderHandle, shaderType);
}

Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath):
    vertexPath(vertexPath),
    fragmentPath(fragmentPath),
    geometryPath(geometryPath)
{
   initialize(vertexPath,fragmentPath,geometryPath);
}


void Shader::initialize(std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
    compileShader(vertexPath,vertexShader,GL_VERTEX_SHADER);
    assert(checkGLError);
    compileShader(fragmentPath,fragmentShader,GL_FRAGMENT_SHADER);
    assert(checkGLError);
    if(!geometryPath.empty())
        compileShader(geometryPath,geometryShader, GL_GEOMETRY_SHADER);

    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    program = glCreateProgram();
    assert(checkGLError);

    if(program == 0)
    {
        ERROR_MESSAGE("Unable to create shader program.", name);
        assert(0);
    }

    glAttachShader(program, vertexShader);
    assert(checkGLError);
    glAttachShader(program, fragmentShader);
    assert(checkGLError);
    if(!geometryPath.empty())
        glAttachShader(program, geometryShader);
    glLinkProgram(program);
    assert(checkGLError);

    initialized = true;
    //maybe later? We'll see
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);
}

GLint Shader::getUniformLocation(std::string name)
{
    if(uniforms.count(name) == 0)
        uniforms[name] = glGetUniformLocation(program, name.c_str());
    return uniforms[name];
}

/*bunch of setuniform boilerplate*/

void Shader::setUniform(std::string name, int data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniform1i(getUniformLocation(name),data);
}
void Shader::setUniform(std::string name, float data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniform1f(getUniformLocation(name),data);
}

void Shader::setUniform(std::string name, const glm::vec2& data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniform2f(getUniformLocation(name),data.x,data.y);
}
void Shader::setUniform(std::string name, const glm::vec3& data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniform3f(getUniformLocation(name),data.x,data.y,data.z);
}
void Shader::setUniform(std::string name, const glm::vec4& data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniform4f(getUniformLocation(name),data.x,data.y, data.z,data.w);
}

void Shader::setUniform(std::string name, const glm::mat2& data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniformMatrix2fv(getUniformLocation(name),1,GL_FALSE,glm::value_ptr(data));
}
void Shader::setUniform(std::string name, const glm::mat3& data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniformMatrix3fv(getUniformLocation(name),1,GL_FALSE,glm::value_ptr(data));
}
void Shader::setUniform(std::string name, const glm::mat4& data, int index = -1)
{
    if(index > -1)
        name = makeIndexUniform(name,index);
    glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,glm::value_ptr(data));
}
