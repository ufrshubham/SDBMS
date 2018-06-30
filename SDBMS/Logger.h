#pragma once

#include "SDBMS_BASE_CLASS.h"
#include <fstream>
#include <string>

namespace SDBMS
{
    class Logger
    {
        std::ofstream logFile;
        Logger();
    public:
        static Logger* CreateLogger();
        void operator << (std::string dumpString);
        void operator << (const int&);
        ~Logger();
    };
}
