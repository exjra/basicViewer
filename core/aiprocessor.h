#ifndef AIPROCESSOR_H
#define AIPROCESSOR_H

#include <thread>
#include <chrono>

class AIProcessor
{
public:
    virtual ~AIProcessor();
    AIProcessor(long long pPeriode);

    virtual void headOfProcess();
    virtual void process() = 0;
    virtual bool beforeStart() = 0;
    virtual bool beforeLoop() = 0;
    virtual bool afterStop() = 0;
    virtual bool endOfLoop() = 0;

    bool start();
    void stop();

protected:
    std::thread *mThread = nullptr;
    bool mThreadRunning = true;

    void localProcess();

    long long mProcessorPeriodeInMillis = 0;
};

#endif // AIPROCESSOR_H
