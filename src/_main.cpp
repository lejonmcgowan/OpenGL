#include "window.h"


int main(void)
{
    Window *window = new Window(640,480,"Test Window");

    window->init(new BasicTriangleScene());
    window->run();
    window->stop();

    return 0;
}
