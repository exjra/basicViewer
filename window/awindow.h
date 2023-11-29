#ifndef AWINDOW_H
#define AWINDOW_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <functional>
#include <string>

class AWindow
{
public:
    virtual ~AWindow();
    AWindow(GLint pX, GLint pY,
            GLint pWidth, GLint pHeight,
            bool pIsFullscreen);

    int init();

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void swapBuffers() { glfwSwapBuffers(mainWindow); }
    void setVsync(bool pVSync);

    GLint getBufferWidth() const;
    GLint getBufferHeight() const;

    GLFWwindow *getMainWindow() const;

    void setKeyHandlerFunction(std::function<void (std::string)> keyHandlerFunction);

    void processKeyboardEvents();

protected:
    GLFWwindow* mainWindow;

    bool mIsFullscreen = false;
    GLint mX, mY;
    GLint mWidth, mHeight;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;

    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);

    std::function < void (std::string) > mKeyHandlerFunction;

    static bool mF12Pressed;
    static int mPressedKeyVal;
    static bool mIsReleased;
};

#endif // AWINDOW_H
