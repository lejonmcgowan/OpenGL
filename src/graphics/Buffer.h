//
// Created by lejonmcgowan on 7/11/15.
//

#ifndef TESTPROJECT2_BUFFER_H
#define TESTPROJECT2_BUFFER_H


#include <GL/glew.h>

#include <vector>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

class Buffer {
private:
    class AttribPointerData
    {
    public:
        int index;
        int elementSize;
        int offset;
        AttribPointerData(int index, int elementSize, int offset):
                index(index),
                elementSize(elementSize),
                offset(offset)
        {}
    };

    GLuint handle;
    std::vector<GLfloat > bufferData;
    std::vector<AttribPointerData> attribPointerData;
    int blockSize;
public:
    Buffer() {}
    Buffer(int blockSize):blockSize(blockSize){}
    ~Buffer(){glDeleteBuffers(1,&handle);}

    GLuint getHandle(){return handle;}

    GLuint addVertexAttribPointer(int attribPointerIndex,int elementSize,int offset);
    void setAttribPointerState( int attribPointerIndex,bool enabled);
    void init(GLenum drawType = GL_STATIC_DRAW);

    void addData(GLfloat  element){ bufferData.push_back(element);}
    void addData(GLfloat element1, GLfloat element2)
    {
        bufferData.push_back(element1);
        bufferData.push_back(element2);
    }
    void addData(GLfloat element1, GLfloat element2, GLfloat element3)
    {
        bufferData.push_back(element1);
        bufferData.push_back(element2);
        bufferData.push_back(element3);
    }
    void addData(GLfloat element1, GLfloat element2, GLfloat element3, GLfloat element4)
    {
        bufferData.push_back(element1);
        bufferData.push_back(element2);
        bufferData.push_back(element3);
        bufferData.push_back(element4);
    }
    void addData(glm::vec2 elements)
    {
        bufferData.push_back(elements.x);
        bufferData.push_back(elements.y);
    }
    void addData(glm::vec3 elements)
    {
        bufferData.push_back(elements.x);
        bufferData.push_back(elements.y);
        bufferData.push_back(elements.z);
    }
    void addData(glm::vec4 elements)
    {
        bufferData.push_back(elements.x);
        bufferData.push_back(elements.y);
        bufferData.push_back(elements.z);
        bufferData.push_back(elements.w);
    }
    void addData(GLfloat elements[], int numElements)
    {
        for(int i = 0; i < numElements; i++)
            bufferData.push_back(elements[i]);
    }
    void addData(std::vector<GLfloat>& elements){ bufferData.insert(bufferData.end(),elements.begin(),elements.end());}
};


#endif //TESTPROJECT2_BUFFER_H
