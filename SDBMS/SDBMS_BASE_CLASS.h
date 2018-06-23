#pragma once
class SDBMS_BASE_CLASS
{
    static int objectId;
public:
    SDBMS_BASE_CLASS();
    ~SDBMS_BASE_CLASS();

    int GetMaxObjectId();
};

