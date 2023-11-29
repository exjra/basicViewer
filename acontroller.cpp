#include "acontroller.h"

#include "helpers/ahelpers.h"


AController::~AController()
{
    if(mRenderer != nullptr)
        delete mRenderer;
}

AController::AController(std::string pFilePath)
{
    mRenderer = new ARenderer(0, 0, 1024, 768, false, pFilePath);
}

void AController::run()
{
    mRenderer->init();

    mRenderer->show();
}
