//
// Created by lejonmcgowan on 9/13/15.
//

#include <glm/gtc/constants.hpp>
#include "SphereBuffer.h"
#include <cmath>

BufferSphere::BufferSphere(float radius, GLuint slices, GLuint stacks):
radius(radius),
slices(slices),
stacks(stacks)
{
    nVerts = (slices+1) * (stacks + 1);
    elements = (slices * 2 * (stacks-1) ) * 3;

    // Verts
    float * v = new float[3 * nVerts];
    // Normals
    float * n = new float[3 * nVerts];
    // Tex coords
    float * tex = new float[2 * nVerts];
    // Elements
    int * el = new int[elements];

    bufferObject.addBuffer("vertexBuffer",3);
    bufferObject.addBuffer("normalBuffer",3);
    bufferObject.addBuffer("texBuffer",2);

    // Generate the vertex data
    generateVerts(v, n, tex, el);

    // Create and populate the buffer objects TODO: make sure removing sizeof(GL_FLOAT) is legit
    bufferObject.getBuffer("vertexBuffer").addData(v,3 * nVerts);
    bufferObject.addBufferVertexAttrib("vertexBuffer",3,0,0);

    bufferObject.getBuffer("normalBuffer").addData(n,3 * nVerts);
    bufferObject.addBufferVertexAttrib("normalBuffer",3,0,1);

    bufferObject.getBuffer("texBuffer").addData(tex,2 * nVerts);
    bufferObject.addBufferVertexAttrib("texBuffer",2,0,2);

    bufferObject.getIndexBuffer().addData(el,elements);

    delete [] v;
    delete [] n;
    delete [] el;
    delete [] tex;

    // DO IT
    bufferObject.init();

    VAOHandle = bufferObject.getVAO();
}

void BufferSphere::generateVerts(float * verts, float * norms, float * tex, int * el)
{
    // Generate positions and normals
    GLfloat theta, phi;
    GLfloat thetaFac = 2 * glm::pi<float>() / slices;
    GLfloat phiFac = glm::pi<float>() / stacks;
    GLfloat nx, ny, nz, s, t;
    GLuint idx = 0, tIdx = 0;
    for( GLuint i = 0; i <= slices; i++ ) {
        theta = i * thetaFac;
        s = (GLfloat)i / slices;
        for( GLuint j = 0; j <= stacks; j++ ) {
            phi = j * phiFac;
            t = (GLfloat)j / stacks;
            nx = sinf(phi) * cosf(theta);
            ny = sinf(phi) * sinf(theta);
            nz = cosf(phi);
            verts[idx] = radius * nx; verts[idx+1] = radius * ny; verts[idx+2] = radius * nz;
            norms[idx] = nx; norms[idx+1] = ny; norms[idx+2] = nz;
            idx += 3;

            tex[tIdx] = s;
            tex[tIdx+1] = t;
            tIdx += 2;
        }
    }

    // Generate the element list
    idx = 0;
    for( GLuint i = 0; i < slices; i++ ) {
        GLuint stackStart = i * (stacks + 1);
        GLuint nextStackStart = (i+1) * (stacks+1);
        for( GLuint j = 0; j < stacks; j++ ) {
            if( j == 0 ) {
                el[idx] = stackStart;
                el[idx+1] = stackStart + 1;
                el[idx+2] = nextStackStart + 1;
                idx += 3;
            } else if( j == stacks - 1) {
                el[idx] = stackStart + j;
                el[idx+1] = stackStart + j + 1;
                el[idx+2] = nextStackStart + j;
                idx += 3;
            } else {
                el[idx] = stackStart + j;
                el[idx+1] = stackStart + j + 1;
                el[idx+2] = nextStackStart + j + 1;
                el[idx+3] = nextStackStart + j;
                el[idx+4] = stackStart + j;
                el[idx+5] = nextStackStart + j + 1;
                idx += 6;
            }
        }
    }
}

void BufferSphere::render()
{
    bufferObject.render(GL_TRIANGLES,elements);
}


