#include "Logger.h"
#include <string>
#include <fstream>
#include <iostream>

SDBMS::Logger::Logger()
{
    std::string fileName("sdbms.sdbmslog");
    logFile.open(fileName);

    if (!logFile.is_open())
    {
        std::cout << "Could not create log file." << std::endl;
    }
}

SDBMS::Logger* SDBMS::Logger::CreateLogger()
{
    static Logger logger;
    return &logger;
}

void SDBMS::Logger::operator<<(std::string dumpString)
{
    if (logFile.is_open())
    {
        logFile << dumpString << std::endl;
    }
}

SDBMS::Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}
