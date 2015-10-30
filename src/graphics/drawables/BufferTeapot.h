//
// Created by lejonmcgowan on 10/29/15.
//

#ifndef TESTPROJECT2_BUFFERTEAPOT_H
#define TESTPROJECT2_BUFFERTEAPOT_H

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec.hpp>

#include "Drawable.h"
#include "BufferObject.h"
#include <glm/glm.hpp>

class BufferTeapot: public Drawable
{
private:
    BufferObject bufferObject;
    unsigned int VAOHandle;
    unsigned int faces;

    void generatePatches(float * vertices, float * normal, float *texCoords, GLint* element, int grid);
    void buildPatchReflect(int patchNum,
                           float *B, float *dB,
                           float *vertices, float *normals, float *texCoords, GLint* elements,
                           int& index, int& elIndex, int &texIndex, int grid,
                           bool reflectX, bool reflectY);
    void buildPatch(glm::vec3 patch[][4],
                    float *B, float *dB,
                    float *vertices, float *normals,float *texCoords, GLint* elements,
                    int &index, int &elIndex, int &texIndex, int grid,glm:: mat3 reflect, bool invertNormal);
    void getPatch( int patchNum, glm::vec3 patch[][4], bool reverseV );

    void computeBasisFunctions( float * B, float * dB, int grid );
    glm::vec3 evaluate( int gridU, int gridV, float *B, glm::vec3 patch[][4] );
    glm::vec3 evaluateNormal( int gridU, int gridV, float *B, float *dB, glm::vec3 patch[][4] );
    void moveLid(int grid, float *vertices, const glm::mat4 lidTransform);
public:
    BufferTeapot(int grid, const glm::mat4& lidTransform);

    void render();


};

#endif //TESTPROJECT2_BUFFERTEAPOT_H
