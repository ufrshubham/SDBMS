#include "Logger.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std::chrono;

#define SIZE 50

SDBMS::Logger::Logger()
{
    std::string fileName("sdbms.sdbmslog");
    logFile.open(fileName);

    if (!logFile.is_open())
    {
        std::cout << "Could not create log file." << std::endl;
    }
    else
    {
        logFile << "Logger started : ";
        LogCurrentTime();
    }
}

SDBMS::Logger* SDBMS::Logger::CreateLogger()
{
    //This is the common logger object
    static Logger logger;
    return &logger;
}

void SDBMS::Logger::LogCurrentTime()
{
    char timeNow[SIZE];

    //Get the current system time
    std::time_t currentTime = system_clock::to_time_t(system_clock::now());

    //I had to wite this hack to eliminate the newline character which is present at the end of
    //char* returned by ctime_s()
    ctime_s(timeNow, SIZE, &currentTime);
    std::string timeStamp(timeNow);
    logFile << timeStamp.substr(0, timeStamp.length() - 1) << std::endl;
}

SDBMS::Logger &SDBMS::operator<<(Logger &stream, std::string dumpString)
{
    GET_LOGGER

    if (logger->logFile.is_open())
    {
        logger->logFile << dumpString;
    }

    return stream;
}

SDBMS::Logger & SDBMS::operator<<(Logger &stream, int number)
{
    GET_LOGGER

    if(logger->logFile.is_open())
    {
        logger->logFile << number;
    }

    return stream;
}

SDBMS::Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile << "Closing logger";
        LogCurrentTime();
        logFile.close();
    }
}
