//
// Created by lejonmcgowan on 10/29/15.
//

#include <GL/glew.h>
#include "TeapotBuffer.h"
#include "teapotdata.h"

BufferTeapot::BufferTeapot(int grid, const glm::mat4 &lidTransform)
{
    int verts = 32 * (grid + 1) * (grid + 1);
    faces = (unsigned int) (grid * grid * 32);
    float * v = new float[ verts * 3 ];
    float * n = new float[ verts * 3 ];
    float *tc = new float[ verts * 2 ];
    GLint* el = new GLint[faces * 6];

    bufferObject.addBuffer("vertexBuffer",3);
    bufferObject.addBuffer("normalBuffer",3);
    bufferObject.addBuffer("texBuffer",2);

    generatePatches( v, n, tc, el, grid );
    moveLid(grid, v, lidTransform);

    bufferObject.getBuffer("vertexBuffer").addData(v,3 * verts);
    bufferObject.addBufferVertexAttrib("vertexBuffer",3,0,0);

    bufferObject.getBuffer("normalBuffer").addData(n,3 * verts);
    bufferObject.addBufferVertexAttrib("normalBuffer",3,0,1);

    bufferObject.getBuffer("texBuffer").addData(tc,2 * verts);
    bufferObject.addBufferVertexAttrib("texBuffer",2,0,2);

    bufferObject.getIndexBuffer().addData(el,6 * faces);

    bufferObject.init();

    VAOHandle = bufferObject.getVAO();

    transform.scaleBy(0.5);
    transform.rotateBy(glm::vec3(glm::radians(-90.0f),0,0));
    transform.translateBy(glm::vec3(0,-0.5f,0));

    delete [] v;
    delete [] n;
    delete [] el;
    delete [] tc;
}

void BufferTeapot::generatePatches(float *vertices, float *normals, float *texCoords, GLint *elements, int grid)
{
    float * B = new float[4*(grid+1)];  // Pre-computed Bernstein basis functions
    float * dB = new float[4*(grid+1)]; // Pre-computed derivitives of basis functions

    int idx = 0, elIndex = 0, tcIndex = 0;

    // Pre-compute the basis functions  (Bernstein polynomials)
    // and their derivatives
    computeBasisFunctions(B, dB, grid);

    // Build each patch
    // The rim
    buildPatchReflect(0, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, true, true);
    // The body
    buildPatchReflect(1, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, true, true);
    buildPatchReflect(2, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, true, true);
    // The lid
    buildPatchReflect(3, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, true, true);
    buildPatchReflect(4, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, true, true);
    // The bottom
    buildPatchReflect(5, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, true, true);
    // The handle
    buildPatchReflect(6, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, false, true);
    buildPatchReflect(7, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, false, true);
    // The spout
    buildPatchReflect(8, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, false, true);
    buildPatchReflect(9, B, dB, vertices, normals, texCoords, elements, idx, elIndex, tcIndex, grid, false, true);

    delete [] B;
    delete [] dB;
}

void BufferTeapot::render()
{
    bufferObject.render(GL_TRIANGLES,6 * faces);
}

void BufferTeapot::buildPatchReflect(int patchNum, float *B, float *dB, float *vertices, float *normals,
                                     float *texCoords, GLint *elements, int &index, int &elIndex, int &texIndex,
                                     int grid, bool reflectX, bool reflectY)
{
    glm::vec3 patch[4][4];
    glm::vec3 patchRevV[4][4];
    getPatch(patchNum, patch, false);
    getPatch(patchNum, patchRevV, true);

    // Patch without modification
    buildPatch(patch, B, dB, vertices, normals, texCoords, elements,
               index, elIndex, texIndex, grid, glm::mat3(1.0f), true);

    // Patch reflected in x
    if( reflectX ) {
        buildPatch(patchRevV, B, dB, vertices, normals, texCoords, elements,
                   index, elIndex, texIndex, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f),
                                                       glm::vec3(0.0f, 1.0f, 0.0f),
                                                       glm::vec3(0.0f, 0.0f, 1.0f) ), false );
    }

    // Patch reflected in y
    if( reflectY ) {
        buildPatch(patchRevV, B, dB, vertices, normals, texCoords, elements,
                   index, elIndex, texIndex, grid, glm::mat3(glm::vec3(1.0f, 0.0f, 0.0f),
                                                       glm::vec3(0.0f, -1.0f, 0.0f),
                                                       glm::vec3(0.0f, 0.0f, 1.0f) ), false );
    }

    // Patch reflected in x and y
    if( reflectX && reflectY ) {
        buildPatch(patch, B, dB, vertices, normals, texCoords, elements,
                   index, elIndex, texIndex, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f),
                                                       glm::vec3(0.0f, -1.0f, 0.0f),
                                                       glm::vec3(0.0f, 0.0f, 1.0f) ), true );
    }
}

void BufferTeapot::buildPatch(glm::vec3 (*patch)[4], float *B, float *dB, float *vertices, float *normals,
                              float *texCoords, GLint *elements, int &index, int &elIndex, int &texIndex,
                              int grid, glm::mat3 reflect, bool invertNormal)
{
    int startIndex = index / 3;
    float tcFactor = 1.0f / grid;

    for( int i = 0; i <= grid; i++ )
    {
        for( int j = 0 ; j <= grid; j++)
        {
            glm::vec3 pt = reflect * evaluate(i,j,B,patch);
            glm::vec3 norm = reflect * evaluateNormal(i,j,B,dB,patch);
            if( invertNormal )
                norm = -norm;

            vertices[index] = pt.x;
            vertices[index+1] = pt.y;
            vertices[index+2] = pt.z;

            normals[index] = norm.x;
            normals[index+1] = norm.y;
            normals[index+2] = norm.z;

            texCoords[texIndex] = i * tcFactor;
            texCoords[texIndex+1] = j * tcFactor;

            index += 3;
            texIndex += 2;
        }
    }

    for(unsigned int i = 0; i < grid; i++ )
    {
        unsigned int iStart = i * (grid+1) + startIndex;
        unsigned int nextiStart = (i+1) * (grid+1) + startIndex;
        for( int j = 0; j < grid; j++)
        {
            elements[elIndex] = iStart + j;
            elements[elIndex+1] = nextiStart + j + 1;
            elements[elIndex+2] = nextiStart + j;

            elements[elIndex+3] = iStart + j;
            elements[elIndex+4] = iStart + j + 1;
            elements[elIndex+5] = nextiStart + j + 1;

            elIndex += 6;
        }
    }
}

void BufferTeapot::getPatch(int patchNum, glm::vec3 (*patch)[4], bool reverseV)
{
    for( int u = 0; u < 4; u++) {          // Loop in u direction
        for( int v = 0; v < 4; v++ ) {     // Loop in v direction
            if( reverseV ) {
                patch[u][v] = glm::vec3(
                        Teapot::cpdata[Teapot::patchdata[patchNum][u*4+(3-v)]][0],
                        Teapot::cpdata[Teapot::patchdata[patchNum][u*4+(3-v)]][1],
                        Teapot::cpdata[Teapot::patchdata[patchNum][u*4+(3-v)]][2]
                );
            } else {
                patch[u][v] = glm::vec3(
                        Teapot::cpdata[Teapot::patchdata[patchNum][u*4+v]][0],
                        Teapot::cpdata[Teapot::patchdata[patchNum][u*4+v]][1],
                        Teapot::cpdata[Teapot::patchdata[patchNum][u*4+v]][2]
                );
            }
        }
    }
}

void BufferTeapot::computeBasisFunctions(float *B, float *dB, int grid)
{
    float inc = 1.0f / grid;
    for( int i = 0; i <= grid; i++ )
    {
        float t = i * inc;
        float tSqr = t * t;
        float oneMinusT = (1.0f - t);
        float oneMinusT2 = oneMinusT * oneMinusT;

        B[i*4 + 0] = oneMinusT * oneMinusT2;
        B[i*4 + 1] = 3.0f * oneMinusT2 * t;
        B[i*4 + 2] = 3.0f * oneMinusT * tSqr;
        B[i*4 + 3] = t * tSqr;

        dB[i*4 + 0] = -3.0f * oneMinusT2;
        dB[i*4 + 1] = -6.0f * t * oneMinusT + 3.0f * oneMinusT2;
        dB[i*4 + 2] = -3.0f * tSqr + 6.0f * t * oneMinusT;
        dB[i*4 + 3] = 3.0f * tSqr;
    }

}

glm::vec3 BufferTeapot::evaluate(int gridU, int gridV, float *B, glm::vec3 (*patch)[4])
{
    glm::vec3 p(0.0f,0.0f,0.0f);
    for( int i = 0; i < 4; i++) {
        for( int j = 0; j < 4; j++) {
            p += patch[i][j] * B[gridU*4+i] * B[gridV*4+j];
        }
    }
    return p;
}

glm::vec3 BufferTeapot::evaluateNormal(int gridU, int gridV, float *B, float *dB, glm::vec3 (*patch)[4])
{
    glm::vec3 du(0.0f,0.0f,0.0f);
    glm::vec3 dv(0.0f,0.0f,0.0f);

    for( int i = 0; i < 4; i++) {
        for( int j = 0; j < 4; j++) {
            du += patch[i][j] * dB[gridU*4+i] * B[gridV*4+j];
            dv += patch[i][j] * B[gridU*4+i] * dB[gridV*4+j];
        }
    }

    glm::vec3 norm = glm::cross(du, dv);
    if (glm::length(norm) != 0.0f) {
        norm = glm::normalize(norm);
    }

    return norm;
}

void BufferTeapot::moveLid(int grid, float *vertices, const glm::mat4 lidTransform)
{
    int start = 3 * 12 * (grid+1) * (grid+1);
    int end = 3 * 20 * (grid+1) * (grid+1);

    for( int i = start; i < end; i+=3 )
    {
        glm::vec4 vert = glm::vec4(vertices[i], vertices[i+1], vertices[i+2], 1.0f );
        vert = lidTransform * vert;
        vertices[i] = vert.x;
        vertices[i+1] = vert.y;
        vertices[i+2] = vert.z;
    }

}

