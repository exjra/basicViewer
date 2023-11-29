#ifndef ARENDERER_H
#define ARENDERER_H

#include <mutex>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "window/awindow.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

template <typename T, typename Total, size_t N>
class AMovingAverage
{
  public:
    AMovingAverage& operator()(T sample)
    {
        total_ += sample;
        if (num_samples_ < N)
            samples_[num_samples_++] = sample;
        else
        {
            T& oldest = samples_[num_samples_++ % N];
            total_ -= oldest;
            oldest = sample;
        }
        return *this;
    }

    operator double() const { return total_ / std::min(num_samples_, N); }

  private:
    T samples_[N];
    size_t num_samples_{0};
    Total total_{0};
};

class ARenderer
{
public:
    virtual ~ARenderer();
    ARenderer(GLint pX, GLint pY, GLint pWidth, GLint pHeight, bool pIsFullscreen, std::string pFilePath);

    void init();
    void show();

    void setKeyHandlerFunction(std::function<void (std::string)> newKeyHandlerFunction);

    void setDefaultFilePath(const std::string &defaultFilePath);

protected:
    AWindow* tMainWindow = nullptr;

    Mesh *tCameraMesh = nullptr;
    Shader* tCameraShader = nullptr;
    Texture* tCameraTexture = nullptr;

    void createWindow();
    void createCameraMesh();
    void createCameraShader();
    void createCameraTexture();

    void renderCamera();

    std::recursive_mutex mActiveCamMutex;
    std::string mActiveCamType = "day"; //false: day, true:ir

    AMovingAverage<float, float, 100> mRenderFpsMAV;
    AMovingAverage<float, float, 100> mCaptureFpsMAV;

    std::function < void (std::string) > mKeyHandlerFunction;

    std::string mDefaultFilePath = "";
    std::string tFragmentShader;
    std::string tVertexShader;
};

#endif // ARENDERER_H
