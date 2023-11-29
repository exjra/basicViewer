#include "arenderer.h"

#include "../helpers/ahelpers.h"

ARenderer::~ARenderer()
{
    //    mCommandListener.deinit();
}

ARenderer::ARenderer(GLint pX, GLint pY,
                     GLint pWidth, GLint pHeight,
                     bool pIsFullscreen, std::string pFilePath)
{
    setDefaultFilePath(pFilePath);
    if(mDefaultFilePath == "")
        mDefaultFilePath = AHelpers::devPath() + "/src/test.png";

    tMainWindow = new AWindow(pX, pY,
                              pWidth, pHeight,
                              pIsFullscreen);
    //    tMainWindow->setKeyHandlerFunction(std::bind(&ARenderer::onKeyCaptured, this, std::placeholders::_1));
}

void ARenderer::init()
{
    createWindow();
    createCameraMesh();
    createCameraShader();
    createCameraTexture();

    //    mCommandListener.init("RendererMessageTopic", "RendererMessage", "Renderer", std::bind(&ARenderer::onCommandReceived, this, std::placeholders::_1));
}

void ARenderer::show()
{
    while(!tMainWindow->getShouldClose())
    {
        glfwPollEvents();

        tMainWindow->processKeyboardEvents();

        renderCamera();

        tMainWindow->swapBuffers();
    }

    delete tMainWindow;
    tMainWindow = nullptr;

    delete tCameraMesh;
    tCameraMesh = nullptr;

    delete tCameraShader;
    tCameraShader = nullptr;

    delete tCameraTexture;
    tCameraTexture = nullptr;
}

void ARenderer::createWindow()
{
    tMainWindow->init();
    tMainWindow->setVsync(true);
}

void ARenderer::createCameraMesh()
{
    unsigned int floorIndices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLfloat floorVertices[] = {
        -1.0f, 1.0f, 0.0f,	0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
        -1.0f, -1.0f, 0.0f,	0.0f, 1.0f,     0.0f, 0.0f, -1.0f,
        1.0f, -1.0f, 0.0f,	1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f,	1.0f, 0.0f,     0.0f, 0.0f, -1.0f
    };

    tCameraMesh = new Mesh();
    tCameraMesh->CreateMesh(floorVertices, floorIndices, 32, 6);
}

void ARenderer::createCameraShader()
{
//    // Vertex Shader
//#if defined(DEPLOY_APP)
//    static const char* vShader = "data/camshader.vert";
//#else
//    std::string tTempStr = AHelpers::devPath() + "/src/renderer/camshader.vert";
//    static const char* vShader = tTempStr.data();
//#endif

//    // Fragment Shader

//#if defined(DEPLOY_APP)
//    static const char* fShader = "data/camshader.frag";
//#else
//    std::string tTempStr2 = AHelpers::devPath() + "/src/renderer/camshader.frag";
//    static const char* fShader = tTempStr2.data();
//#endif

//    tCameraShader = new Shader();
//    tCameraShader->CreateFromFiles(vShader, fShader);


    tVertexShader = "#version 330                                               \n" \
                                "                                                           \n" \
                                "layout (location = 0) in vec3 pos;                         \n" \
                                "layout (location = 1) in vec2 tex;                         \n" \
                                "layout (location = 2) in vec3 norm;                        \n" \
                                "                                                           \n" \
                                "out vec2 TexCoord;                                         \n" \
                                "                                                           \n" \
                                "uniform mat4 model;                                        \n" \
                                "uniform mat4 projection;                                   \n" \
                                "uniform mat4 view;                                         \n" \
                                "                                                           \n" \
                                "void main()                                                \n" \
                                "{                                                          \n" \
                                "//        gl_Position = vec4(pos*2-1, 1.0);                \n" \
                                "        gl_Position = projection * vec4(pos, 1.0);         \n" \
                                "//        gl_Position = vec4(pos, 1.0);                    \n" \
                                "                                                           \n" \
                                "        TexCoord = tex;                                    \n" \
                                "}                                                          \n";

    tFragmentShader = "#version 330                                                                                 \n" \
                      "                                                                                             \n" \
                      "in vec2 TexCoord;                                                                            \n" \
                      "                                                                                             \n" \
                      "out vec4 colour;                                                                             \n" \
                      "                                                                                             \n" \
                      "uniform sampler2D theTexture;                                                                \n" \
                      "                                                                                             \n" \
                      "void main()                                                                                  \n" \
                      "{                                                                                            \n" \
                      "//    colour = texture(theTexture, TexCoord);                                                \n" \
                      "                                                                                             \n" \
                      "    vec4 texColor = texture(theTexture, TexCoord);                                           \n" \
                      "//    if(texColor.a < 0.01)                                                                  \n" \
                      "//        discard;                                                                           \n" \
                      "    colour = vec4(texColor.r, texColor.g, texColor.b, texColor.w); //bgr convertion          \n" \
                      "                                                                                             \n" \
                      "    //emboss effect                                                                          \n" \
                      "    /*                                                                                       \n" \
                      "    vec2 onePixel = vec2(1.0 / 480.0, 1.0 / 320.0);                                          \n" \
                      "                                                                                             \n" \
                      "    vec4 color;                                                                              \n" \
                      "    color.rgb = vec3(0.5);                                                                   \n" \
                      "    color -= texture2D(theTexture, TexCoord - onePixel) * 5.0;                               \n" \
                      "    color += texture2D(theTexture, TexCoord + onePixel) * 5.0;                               \n" \
                      "                                                                                             \n" \
                      "    color.rgb = vec3((color.r + color.g + color.b) / 3.0);                                   \n" \
                      "    colour = vec4(color.rgb, 1);                                                             \n" \
                      "    */                                                                                       \n" \
                      "}                                                                                            \n";

    static const char* vShader = tVertexShader.data();
    static const char* fShader = tFragmentShader.data();

    tCameraShader = new Shader();
    tCameraShader->CreateFromString(vShader, fShader);
}

void ARenderer::createCameraTexture()
{
    tCameraTexture = new Texture(mDefaultFilePath.data());

    tCameraTexture->LoadTextureA();
}

void ARenderer::renderCamera()
{
    glViewport(0, 0, tMainWindow->getBufferWidth(), tMainWindow->getBufferHeight());

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tCameraShader->UseShader();

    //    glm::mat4 projection = glm::perspective(glm::radians(60.0f), ((GLfloat)tMainWindow->getBufferWidth()) / ((GLfloat)tMainWindow->getBufferHeight()), 0.1f, 100.0f);
    //    glm::mat4 projection = glm::ortho(0.0f, (float)tMainWindow->getBufferWidth(), 0.0f, (float)tMainWindow->getBufferHeight(), 0.1f, 100.0f);
    //    glm::mat4 projection = glm::ortho(0.0f, -1.0f, 0.0f, -1.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix;
    glm::mat4 projection(1.0f);
    glUniformMatrix4fv(tCameraShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(tCameraShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(viewMatrix));

    tCameraShader->Validate();

    glm::mat4 model(1.0f);
    glUniformMatrix4fv(tCameraShader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

//    std::lock_guard<std::recursive_mutex> lk(mActiveCamMutex);
//    tCameraTexture->updateImage(nullptr, 0, 0);

    tCameraTexture->UseTexture();
    tCameraMesh->RenderMesh();
}

void ARenderer::setDefaultFilePath(const std::string &defaultFilePath)
{
    mDefaultFilePath = defaultFilePath;
}

void ARenderer::setKeyHandlerFunction(std::function<void (std::string)> newKeyHandlerFunction)
{
    mKeyHandlerFunction = newKeyHandlerFunction;
}
