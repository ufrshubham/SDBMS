#include "SDBMS_BASE_CLASS.h"
#include "Logger.h"

int SDBMS::SDBMS_BASE_CLASS::objectId = 0;

SDBMS::SDBMS_BASE_CLASS::SDBMS_BASE_CLASS()
{
    ++objectId;
    //SDBMS::Logger *log = SDBMS::Logger::CreateLogger();

    //if (log != nullptr)
    //{
    //    *log << "Object ";
    //    *log << typeid(this).name();
    //    *log << objectId;
    //    *log<< "created.\n";
    //}
}


SDBMS::SDBMS_BASE_CLASS::~SDBMS_BASE_CLASS()
{
    --objectId;
}

int SDBMS::SDBMS_BASE_CLASS::GetMaxObjectId()
{
    return objectId;
}
