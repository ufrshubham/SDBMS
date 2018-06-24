//This is the base class of all the class of SDBMS

#pragma once

namespace SDBMS
{
    class SDBMS_BASE_CLASS
    {
        static int objectId; //stores the objectId
    public:
        SDBMS_BASE_CLASS();
        ~SDBMS_BASE_CLASS();

        int GetMaxObjectId(); //used to get the max object id
    };

}
