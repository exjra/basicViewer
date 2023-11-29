#ifndef ACMDLINEPARSER_H
#define ACMDLINEPARSER_H

#include <string>
#include <vector>

class ACommandLineParser
{
public:
    ACommandLineParser (int &argc, char **argv);

    const std::string& getCmdOption(const std::string &option) const;
    bool cmdOptionExists(const std::string &option) const;

private:
    std::vector <std::string> tokens;
};

#endif // ACMDLINEPARSER_H
