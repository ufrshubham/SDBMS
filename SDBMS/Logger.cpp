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
    //This is the common logger object
    static Logger logger;
    return &logger;
}

std::string SDBMS::Logger::operator<<(std::string dumpString)
{
    if (logFile.is_open())
    {
        logFile << dumpString << std::endl;
    }

    return dumpString;
}

void SDBMS::Logger::operator<<(const int & objectId)
{
    if (logFile.is_open())
    {
        logFile << objectId;
    }
}

SDBMS::Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}
