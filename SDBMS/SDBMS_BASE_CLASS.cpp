#include "SDBMS_BASE_CLASS.h"
#include "Logger.h"

int SDBMS::SDBMS_BASE_CLASS::objectId = 0;

GET_LOGGER

SDBMS::SDBMS_BASE_CLASS::SDBMS_BASE_CLASS()
{
    DUMP_FUNCTION_INFO

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
    DUMP_FUNCTION_INFO
    --objectId;
}

int SDBMS::SDBMS_BASE_CLASS::GetMaxObjectId()
{
    DUMP_FUNCTION_INFO
    return objectId;
}
