#include "scenes/SceneIncludes.h"
#include "scenes/window.h"


int main()
{
    WindowContexts::WINDOW_WIDTH = 640 * 2;
    WindowContexts::WINDOW_HEIGHT = 480 * 2;

    Window *window = new Window(WindowContexts::WINDOW_WIDTH,WindowContexts::WINDOW_HEIGHT,"Test Window");

    window->init(new MultipleLightsScene());
    window->run();
    window->stop();

    return 0;
}
