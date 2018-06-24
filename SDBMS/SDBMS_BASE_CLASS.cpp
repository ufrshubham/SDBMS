#include "SDBMS_BASE_CLASS.h"

int SDBMS::SDBMS_BASE_CLASS::objectId = 0;

SDBMS::SDBMS_BASE_CLASS::SDBMS_BASE_CLASS()
{
    ++objectId;
}


SDBMS::SDBMS_BASE_CLASS::~SDBMS_BASE_CLASS()
{
    --objectId;
}

int SDBMS::SDBMS_BASE_CLASS::GetMaxObjectId()
{
    return objectId;
}
