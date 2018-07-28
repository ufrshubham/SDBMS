//This is the base class of all the class of SDBMS

#pragma once

namespace SDBMS
{
    class SDBMS_BASE_CLASS
    {
        static int maxUsedObjectId; //stores the max used objectId
        int objectId;               //stores the object id of current object
    public:
        SDBMS_BASE_CLASS();
        ~SDBMS_BASE_CLASS();

        int GetObjectId(); //used to get the max object id
    };

}
