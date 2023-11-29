#ifndef AHELPERS_H
#define AHELPERS_H

#include <string>
#include <chrono>
#include <vector>

#include <iostream>

#define debugOut(x) std::cout << x << std::endl

class AHelpers
{
public:
    static bool fileExists(std::string pFilePath);

    static std::string devPath();
    static std::string getTimedFileName();
    static std::string floatToString(float pVal, int pPrec);
    static std::string decimalToBinary8(uint8_t pVal);

    static uint64_t timeSinceEpochMillisec();

private:
    AHelpers();
};

#endif // AHELPERS_H
