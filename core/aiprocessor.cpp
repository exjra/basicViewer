#include "aiprocessor.h"

#include <functional>

AIProcessor::~AIProcessor()
{
    stop();
}

AIProcessor::AIProcessor(long long pPeriode) :
    mProcessorPeriodeInMillis(pPeriode)
{

}

void AIProcessor::headOfProcess()
{

}

bool AIProcessor::start()
{
    beforeStart();

    mThread = new std::thread(std::bind(&AIProcessor::localProcess, this));

    return true;
}

void AIProcessor::stop()
{
    if(mThread != nullptr)
    {
        mThreadRunning = false;

        if(mThread->joinable())
        {
            mThread->join();

            delete mThread;
            mThread = nullptr;
        }
    }

    afterStop();
}

void AIProcessor::localProcess()
{
    beforeLoop();

    while(mThreadRunning)
    {
        headOfProcess();

        process();

        if(mProcessorPeriodeInMillis != 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(mProcessorPeriodeInMillis));
    }

    endOfLoop();
}
