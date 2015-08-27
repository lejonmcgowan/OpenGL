# OpenGLWrapper
A small abstraction of the typical OpenGL operations needed in computer graphics, like textures, shaders, Camera, etc.

Currently, there is a wrapper implementatoin for maaking buffers, textures, shaders, and cameras. The -Manager classes provide
a singular entity to keepp track of multiple buffers and shaders. THe general flow goes:

1. define dimensions in main  
2. make a class that extends from Scene  (make sure to include the new class in src/CmakeLists.txt
3. make shaders, save into shd/  
4. pass in your Scene into the Window constructed in main
5. run cmake (cmake . if in the root repository, or if out of build make, cmake [path/to/root]) to generate a Makefile
6. run make. to build excecutable

**Dependencies**:

[GLEW](http://glew.sourceforge.net/)  
[GLFW](http://www.glfw.org/)  
[GLM](http://glm.g-truc.net/0.9.7/index.html)  
[SOIL](http://www.lonesock.net/soil.html)  

