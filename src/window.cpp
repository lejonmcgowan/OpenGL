#include <assert.h>
#include "window.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

Window::Window(int width, int height, std::string name):
    WINDOW_NAME(name),
    WINDOW_WIDTH(width),
    WINDOW_HEIGHT(height)
{
    assert(WINDOW_WIDTH == WindowContexts::WINDOW_WIDTH);
    assert(WINDOW_HEIGHT == WindowContexts::WINDOW_HEIGHT);
}

void Window::init(Scene* scene)
{
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,WINDOW_NAME.c_str(),
                              NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetErrorCallback(error_callback);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    checkGLError;//gonna get invalid enum. can't do anything about it.

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    this->scene = scene;
    glfwSetKeyCallback(window,&Keyboard::glfwKeyboardCallback);

    std::cout << "scene assigned" << std::endl;
    this->scene->init();
    std::cout << "scene initialized" << std::endl;

    glEnable(GL_DEPTH_TEST);
}
void Window::processKeys()
{
    if(keyboard.keyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);
}
void Window::run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processKeys();
        scene->processKeys(keyboard);

        scene->update();
        scene->render();

        glfwSwapBuffers(window);
    }
}

void Window::stop()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
