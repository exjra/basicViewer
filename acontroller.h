#ifndef ACONTROLLER_H
#define ACONTROLLER_H

#include "renderer/arenderer.h"


class AController
{
public:
    virtual ~AController();
    AController(std::string pFilePath);

    enum class RunModes
    {
        Stable,
        Settings,
        MemoryView,
        HWMonitor
    };

    void run();

protected:
    //renderer
    ARenderer* mRenderer = nullptr;
};

#endif // ACONTROLLER_H
