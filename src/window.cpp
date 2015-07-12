#include <assert.h>
#include "window.h"

int checkForOpenGLErro(const char * file, int line) {
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        const char * message = "";
        switch( glErr )
        {
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
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

Window::Window(int width, int height, std::string name):
    WINDOW_WIDTH(width),
    WINDOW_HEIGHT(height),
    WINDOW_NAME(name)
{
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
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }
    checkForOpenGLErro(__FILE__,__LINE__); //gonna get invalid enum. can't do anything about it.
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    this->scene = scene;
    std::cout << "scene assigned" << std::endl;
    this->scene->init();
    std::cout << "scene initialized" << std::endl;
}
void Window::run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

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
