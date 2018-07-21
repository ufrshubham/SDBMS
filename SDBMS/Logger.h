#pragma once

#include "SDBMS_BASE_CLASS.h"
#include <fstream>
#include <string>

namespace SDBMS
{
    class Logger
    {
        std::ofstream logFile; //output stream object to handle the log file
        Logger();
    public:
        static Logger* CreateLogger();

        std::string operator << (std::string dumpString); //overload to dump string into log file
        void operator << (const int&); //overload to dump int into log file
        ~Logger();
    };
}
