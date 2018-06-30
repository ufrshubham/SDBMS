#pragma once

#include "SDBMS_BASE_CLASS.h"
#include <fstream>
#include <string>

namespace SDBMS
{
    class Logger :
        public SDBMS_BASE_CLASS
    {
        std::ofstream logFile;
        Logger();
    public:
        static Logger* CreateLogger();
        void operator << (std::string dumpString);
        ~Logger();
    };
}
