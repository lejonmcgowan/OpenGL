//
// Created by lejonmcgowan on 7/12/15.
//

#ifndef TESTPROJECT2_INDEXBUFFER_H
#define TESTPROJECT2_INDEXBUFFER_H

#include <GL/glew.h>

#include <vector>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

class IndexBuffer {
private:
    GLuint handle;
    std::vector<GLuint > bufferData;
public:
    IndexBuffer(){}
    GLuint getHandle(){return handle;}

    void init(GLenum drawType);

    void addData(GLuint  element){ bufferData.push_back(element);}
    void addData(GLuint element1, GLuint element2)
    {
        bufferData.push_back(element1);
        bufferData.push_back(element2);
    }
    void addData(GLuint element1, GLuint element2, GLuint element3)
    {
        bufferData.push_back(element1);
        bufferData.push_back(element2);
        bufferData.push_back(element3);
    }
    void addData(GLuint element1, GLuint element2, GLuint element3, GLuint element4)
    {
        bufferData.push_back(element1);
        bufferData.push_back(element2);
        bufferData.push_back(element3);
        bufferData.push_back(element4);
    }
    void addData(glm::ivec2 elements)
    {
        bufferData.push_back(elements.x);
        bufferData.push_back(elements.y);
    }
    void addData(glm::ivec3 elements)
    {
        bufferData.push_back(elements.x);
        bufferData.push_back(elements.y);
        bufferData.push_back(elements.z);
    }
    void addData(glm::ivec4 elements)
    {
        bufferData.push_back(elements.x);
        bufferData.push_back(elements.y);
        bufferData.push_back(elements.z);
        bufferData.push_back(elements.w);
    }
    void addData(GLuint elements[], int numElements)
    {
        for(int i = 0; i < numElements; i++)
            bufferData.push_back(elements[i]);
    }
    void addData(std::vector<GLuint>& elements){ bufferData.insert(bufferData.end(),elements.begin(),elements.end());}
};

#endif //TESTPROJECT2_INDEXBUFFER_H
