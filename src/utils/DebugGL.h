//
// Created by lejonmcgowan on 6/27/15.
//

#ifndef TESTPROJECT2_DEBUGGL_H
#define TESTPROJECT2_DEBUGGL_H

#include <GL/glew.h>
#include <stdio.h>

#define checkGLError !debugGL::checkErrors(__FILE__,__LINE__)

namespace debugGL{
    static bool firstError = true; //for the Glew error that inevitably pops up. Should'nt have to print to output for that
    static int checkErrors(const char * file, int line) {
        //
        // Returns 1 if an OpenGL error occurred, 0 otherwise.
        //
        GLenum glErr;
        int    retCode = 0;

        glErr = glGetError();
        while (glErr != GL_NO_ERROR) {
            const char *message = "";
            switch (glErr) {
                case GL_INVALID_ENUM:
                    message = "Invalid enum";
                    break;
                case GL_INVALID_VALUE:
                    message = "Invalid value";
                    break;
                case GL_INVALID_OPERATION:
                    message = "Invalid operation";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    message = "Invalid framebuffer operation";
                    break;
                case GL_OUT_OF_MEMORY:
                    message = "Out of memory";
                    break;
                default:
                    message = "Unknown error";
            }
            if (debugGL::firstError)
                printf("glError in file %s @ line %d: %s\n", file, line, message);
            else
                debugGL::firstError = false;
            retCode = 1;
            glErr = glGetError();
        }
        return retCode;
    }
}
#endif //TESTPROJECT2_DEBUGGL_H
