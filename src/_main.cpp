#include "window.h"
#include <iostream>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>

#define GetCurrentDir getcwd
#endif

char cCurrentPath[FILENAME_MAX];

int main(void)
{
    std::cout << "program start!" << std::endl;
    std::cout << GetCurrentDir << std::endl;
    Window *window = new Window(640,480,"Test Window");
    std::cout << "window made" << std::endl;
    window->init(new BasicTriangleScene());
    std::cout << "window initialized" << std::endl;
    window->run();
    window->stop();

    return 0;
}
