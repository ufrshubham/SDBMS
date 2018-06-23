#include "SDBMS_BASE_CLASS.h"

int SDBMS_BASE_CLASS::objectId = 0;

SDBMS_BASE_CLASS::SDBMS_BASE_CLASS()
{
    ++objectId;
}


SDBMS_BASE_CLASS::~SDBMS_BASE_CLASS()
{
    --objectId;
}

int SDBMS_BASE_CLASS::GetMaxObjectId()
{
    return objectId;
}
