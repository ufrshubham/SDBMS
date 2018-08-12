#pragma once

#include "SDBMS_BASE_CLASS.h"
#include <fstream>
#include <string>

//This macro gets the current file, line and function number
#define DUMP_INFO std::string(std::string(__FILE__) + ':' + std::to_string(__LINE__) + ':' + std::string(__FUNCTION__) + "\n");

//We don't want to dump data in release build for now
#ifdef _DEBUG
#define DUMP_FUNCTION_INFO *logger << DUMP_INFO
#define GET_LOGGER static SDBMS::Logger *logger = SDBMS::Logger::CreateLogger();
#define DUMP_SPAWN *logger << "Object with ID:" << GetObjectId() << " of " << typeid(*this).name() << " spawned\n";
#define DUMP_DESTROY *logger << "Object with ID:" << GetObjectId() << " of " << typeid(*this).name() << " destroyed\n";
#else
#define DUMP_FUNCTION_INFO
#define GET_LOGGER
#define DUMP_SPAWN
#define DUMP_DESTROY
#endif

namespace SDBMS
{
    class Logger
    {
        std::ofstream logFile; //output stream object to handle the log file
        Logger();
    public:
        static Logger* CreateLogger();
        void LogCurrentTime(); //this will dump the current system time in log file
        friend Logger& operator<< (Logger&, std::string dumpString); //overload to dump string into log file
        friend Logger& operator<< (Logger&, int); //overload to dump int into log file
        ~Logger();
    };
}
