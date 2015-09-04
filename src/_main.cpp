#include "window.h"
#include "utils/WindowContexts.h"


int main(void)
{
    WindowContexts::WINDOW_WIDTH = 640;
    WindowContexts::WINDOW_HEIGHT = 480;

    Window *window = new Window(WindowContexts::WINDOW_WIDTH,WindowContexts::WINDOW_HEIGHT,"Test Window");

    window->init(new BasicBillboardScene());
    window->run();
    window->stop();

    return 0;
}
