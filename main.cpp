#define STB_IMAGE_IMPLEMENTATION

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "acontroller.h"
#include "helpers/ahelpers.h"
#include "helpers/acmdlineparser.h"

int main(int argc, char **argv)
{
    std::string tFilePath = "";

    ACommandLineParser tCmdParser(argc, argv);

    //-file E:/Projects/aydolabs/basicViewer/src/test.png

    if(tCmdParser.cmdOptionExists("-file"))
    {
        const std::string &tFile = tCmdParser.getCmdOption("-file");

        tFilePath = tFile;
    }

    AController *tCnt = new AController(tFilePath);

    tCnt->run();

    return 0;
}
