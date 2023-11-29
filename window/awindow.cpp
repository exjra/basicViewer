#include "awindow.h"

#include <iostream>
#include <string>

bool AWindow::mF12Pressed = false;
int AWindow::mPressedKeyVal = -1;
bool AWindow::mIsReleased = false;

AWindow::~AWindow()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

AWindow::AWindow(GLint pX, GLint pY,
        GLint pWidth, GLint pHeight,
        bool pIsFullscreen) :
    mX(pX)
  , mY(pY)
  , mWidth(pWidth)
  , mHeight(pHeight)
  , mIsFullscreen(pIsFullscreen)
{
    for(size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
}

int AWindow::init()
{
    if (!glfwInit())
    {
        std::cout << "Error Initialising GLFW!" << std::endl;

        glfwTerminate();
        return 1;
    }

    // Setup GLFW Windows Properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatiblity
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    if(!mIsFullscreen)
        mainWindow = glfwCreateWindow(mWidth, mHeight, "Simple Viewer App", NULL, NULL);
    else
        mainWindow = glfwCreateWindow(mWidth, mHeight, "Simple Viewer App", glfwGetPrimaryMonitor(), NULL);

    if (!mainWindow)
    {
        std::cout << "Error creating GLFW window!" << std::endl;

        glfwTerminate();
        return 1;
    }

    // Get buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set the current context
    glfwMakeContextCurrent(mainWindow);

    // Handle Key + Mouse Input
    createCallbacks();
    //    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Allow modern extension access
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        std::cout << "Error: " << std::string((char*) glewGetErrorString(error)) << std::endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    //    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create Viewport
    glViewport(mX, mY, bufferWidth, bufferHeight);

    std::cout << "Display: " << bufferWidth << "x" << bufferHeight << std::endl;

    glfwSetWindowUserPointer(mainWindow, this);

    return 0;
}

void AWindow::setVsync(bool pVSync)
{
    if(pVSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

GLint AWindow::getBufferWidth() const
{
    return bufferWidth;
}

GLint AWindow::getBufferHeight() const
{
    return bufferHeight;
}

GLFWwindow *AWindow::getMainWindow() const
{
    return mainWindow;
}

void AWindow::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void AWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    (void) code;
    (void) mode;

    AWindow* theWindow = static_cast<AWindow*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (key == GLFW_KEY_F12 && action == GLFW_PRESS)
    {
        mF12Pressed = true;
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;

            mPressedKeyVal = key;
            mIsReleased = false;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;

            mPressedKeyVal = key;
            mIsReleased = true;
        }
    }
}

void AWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    AWindow* theWindow = static_cast<AWindow*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = (float) xPos;
        theWindow->lastY = (float) yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = ((float) xPos) - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - ((float) yPos);

    theWindow->lastX = (float) xPos;
    theWindow->lastY = (float) yPos;
}

void AWindow::setKeyHandlerFunction(std::function<void (std::string)> keyHandlerFunction)
{
    mKeyHandlerFunction = keyHandlerFunction;
}

void AWindow::processKeyboardEvents()
{
    if(mF12Pressed)
    {
        mF12Pressed = false;

        if(mKeyHandlerFunction)
            mKeyHandlerFunction("F12");
    }

    if(mPressedKeyVal != -1)
    {
        if(mKeyHandlerFunction)
            mKeyHandlerFunction(std::to_string(mPressedKeyVal)+(mIsReleased ? "R" : "P"));

        mPressedKeyVal = -1;
    }
}
