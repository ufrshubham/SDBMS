#include "ClassRoomData.h"
#include "StudentData.h"


ClassRoomData::ClassRoomData()
{
}


ClassRoomData::~ClassRoomData()
{
}

int ClassRoomData::GetClassRoomNumber()
{
    return m_classRoomNumber;
}

void ClassRoomData::SetClassRoomNumber(const int classRoomNumber)
{
    m_classRoomNumber = classRoomNumber;
}

int ClassRoomData::GetNumberOfStudents()
{
    return m_numberOfStudents;
}

void ClassRoomData::SetNumberOfStudents(const int numberOfStudent)
{
    m_numberOfStudents = numberOfStudent;
}

std::vector<StudentData> ClassRoomData::GetStudentsData()
{
    return m_studentData;
}

void ClassRoomData::SetStudentsData(const std::vector<StudentData> studData)
{
    m_studentData = studData;
}
