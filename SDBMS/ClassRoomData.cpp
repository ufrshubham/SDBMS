#include "ClassRoomData.h"
#include "StudentData.h"


SDBMS::ClassRoomData::ClassRoomData()
{
}


SDBMS::ClassRoomData::~ClassRoomData()
{
}

int SDBMS::ClassRoomData::GetClassRoomNumber()
{
    return m_classRoomNumber;
}

void SDBMS::ClassRoomData::SetClassRoomNumber(const int classRoomNumber)
{
    m_classRoomNumber = classRoomNumber;
}

int SDBMS::ClassRoomData::GetNumberOfStudents()
{
    return m_numberOfStudents;
}

void SDBMS::ClassRoomData::SetNumberOfStudents(const int numberOfStudent)
{
    m_numberOfStudents = numberOfStudent;
}

std::vector<SDBMS::StudentData> SDBMS::ClassRoomData::GetStudentsData()
{
    return m_studentData;
}

void SDBMS::ClassRoomData::SetStudentsData(const std::vector<SDBMS::StudentData> studData)
{
    m_studentData = studData;
}
