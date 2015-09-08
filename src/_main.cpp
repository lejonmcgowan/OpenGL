#include "scenes/window.h"


int main(void)
{
    WindowContexts::WINDOW_WIDTH = 640;
    WindowContexts::WINDOW_HEIGHT = 480;

    Window *window = new Window(WindowContexts::WINDOW_WIDTH,WindowContexts::WINDOW_HEIGHT,"Test Window");

    window->init(new BasicTriangleScene());
    window->run();
    window->stop();

    return 0;
}
