#pragma once

#include "SDBMS_BASE_CLASS.h"
#include <fstream>
#include <string>

//This macro gets the current file, line and function number
#define DUMP_INFO std::string(std::string(__FILE__) + ':' + std::to_string(__LINE__) + ':' + std::string(__FUNCTION__));

//We don't want to dump data in release build for now
#ifdef _DEBUG
#define DUMP_FUNCTION_INFO *logger << DUMP_INFO
#define GET_LOGGER static SDBMS::Logger *logger = SDBMS::Logger::CreateLogger();
#else
#define DUMP_FUNCTION_INFO
#define GET_LOGGER
#endif

namespace SDBMS
{
    class Logger
    {
        std::ofstream logFile; //output stream object to handle the log file
        Logger();
    public:
        static Logger* CreateLogger();

        friend Logger& operator<< (Logger&, std::string dumpString); //overload to dump string into log file
        void operator << (const int&); //overload to dump int into log file
        ~Logger();
    };
}
