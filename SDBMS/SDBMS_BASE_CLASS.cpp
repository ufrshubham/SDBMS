#include "SDBMS_BASE_CLASS.h"

int SDBMS::SDBMS_BASE_CLASS::maxUsedObjectId = 0;

SDBMS::SDBMS_BASE_CLASS::SDBMS_BASE_CLASS()
{
    objectId = ++maxUsedObjectId;
}


SDBMS::SDBMS_BASE_CLASS::~SDBMS_BASE_CLASS()
{
}

int SDBMS::SDBMS_BASE_CLASS::GetObjectId()
{
    return objectId;
}
