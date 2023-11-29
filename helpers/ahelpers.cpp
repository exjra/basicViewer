#include "ahelpers.h"

#include <sys/stat.h>

#include <chrono>
#include <iomanip> // put_time
#include <fstream>
#include <sstream> // stringstream
#include <bitset>
#include <cstdlib>

bool AHelpers::fileExists(std::string pFilePath)
{
    struct stat buffer;
    return (stat (pFilePath.c_str(), &buffer) == 0);
}

std::string AHelpers::devPath()
{
    char* ADEV_DIR = getenv("ADEV_DIR");
    if(ADEV_DIR != NULL)
    {
        std::string tRet(ADEV_DIR);
        return tRet;
    }
    else
        return ".";
}

std::string AHelpers::getTimedFileName()
{
    auto now = std::chrono::system_clock::now();
    auto UTC = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    return std::to_string(UTC);
}

std::string AHelpers::floatToString(float pVal, int pPrec)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(pPrec) << pVal;
    return stream.str();
}

std::string AHelpers::decimalToBinary8(uint8_t pVal)
{
    return std::bitset<8>(pVal).to_string();
}

uint64_t AHelpers::timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
