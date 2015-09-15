//
// Created by lejonmcgowan on 9/12/15.
//

#include "PlaneBuffer.h"

PlaneBuffer::PlaneBuffer(float xsize, float zsize, int xdivs, int zdivs, float smax, float tmax)
{
    faces = xdivs * zdivs;
    int vSize = 3 * (xdivs + 1) * (zdivs + 1);
    float * v = new float[vSize];

    int nSize = 3 * (xdivs + 1) * (zdivs + 1);
    float * n = new float[nSize];

    int texSize = 2 * (xdivs + 1) * (zdivs + 1);
    float * tex = new float[texSize];

    int elSize = 6 * xdivs * zdivs;
    int *el = new int[elSize];

    bufferObject.addBuffer("vertexBuffer",3);
    bufferObject.addBuffer("normalBuffer",3);
    bufferObject.addBuffer("texBuffer",2);

    float x2 = xsize / 2.0f;
    float z2 = zsize / 2.0f;
    float iFactor = (float)zsize / zdivs;
    float jFactor = (float)xsize / xdivs;
    float texi = smax / zdivs;
    float texj = tmax / xdivs;
    float x, z;
    int vidx = 0, tidx = 0;
    for( int i = 0; i <= zdivs; i++ )
    {
        z = iFactor * i - z2;
        for( int j = 0; j <= xdivs; j++ )
        {
            x = jFactor * j - x2;
            v[vidx] = x;
            v[vidx+1] = 0.0f;
            v[vidx+2] = z;
            n[vidx] = 0.0f;
            n[vidx+1] = 1.0f;
            n[vidx+2] = 0.0f;
            vidx += 3;
            tex[tidx] = j * texi;
            tex[tidx+1] = i * texj;
            tidx += 2;
        }
    }
    bufferObject.getBuffer("vertexBuffer").addData(v,vSize * (int)sizeof(GLfloat));
    bufferObject.addBufferVertexAttrib("vertexBuffer",3,0);

    bufferObject.getBuffer("normalBuffer").addData(n,nSize * (int)sizeof(GLfloat));
    bufferObject.addBufferVertexAttrib("normalBuffer",3,0);

    bufferObject.getBuffer("texBuffer").addData(tex,texSize * (int)sizeof(GLfloat));
    bufferObject.addBufferVertexAttrib("texBuffer",2,0);

    int rowStart, nextRowStart;
    int idx = 0;
    for( int i = 0; i < zdivs; i++ )
    {
        rowStart = i * (xdivs+1);
        nextRowStart = (i+1) * (xdivs+1);
        for( int j = 0; j < xdivs; j++ )
        {
            el[idx] = rowStart + j;
            el[idx+1] = nextRowStart + j;
            el[idx+2] = nextRowStart + j + 1;
            el[idx+3] = rowStart + j;
            el[idx+4] = nextRowStart + j + 1;
            el[idx+5] = rowStart + j + 1;
            idx += 6;
        }
    }
    bufferObject.getIndexBuffer().addData(el,elSize * (int)sizeof(GLfloat));

    bufferObject.init();

    delete [] v;
    delete [] n;
    delete [] tex;
    delete [] el;
}

void PlaneBuffer::render()
{
    bufferObject.render(GL_TRIANGLES, 6 * faces);
}
