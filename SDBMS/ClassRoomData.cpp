#include "ClassRoomData.h"
#include "StudentData.h"

SDBMS::ClassRoomData::ClassRoomData(int classRoomNumber, int numberOfStudents) : m_classRoomNumber(classRoomNumber), m_numberOfStudents(numberOfStudents)
{
    //Since we have number of students and class room number we can initialize the deque 
    //with those values. Here we will set the size of m_studentData as m_numberOfStudents and
    //we will also initialize each element of this deque with m_classRoomNumber. This will
    //internally call the constructor of StudentData with m_classRoomNumber as an argument.
    m_studentData = std::deque<SDBMS::StudentData>(m_numberOfStudents, m_classRoomNumber);
    
    m_maxRollNumber = 0;

    //This loop is written to set the roll numbers of all the students. This is done by 
    //m_maxRollNumber stored in ClassRoomData. It will have initial value of 0 and as we 
    //go on adding student data it will increment by 1. In this way ClassRoomData will
    //always have the last roll number with it.
    for (auto itr = m_studentData.begin(); itr != m_studentData.end(); ++itr)
    {
        itr->SetRollNumber(++m_maxRollNumber);
    }
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

int SDBMS::ClassRoomData::GetMaxRollNumber()
{
    return m_maxRollNumber;
}

void SDBMS::ClassRoomData::SetMaxRollNumber(const int maxRollNumber)
{
    m_maxRollNumber = maxRollNumber;
}

std::deque<SDBMS::StudentData>* SDBMS::ClassRoomData::GetStudentsData()
{
    return &m_studentData;
}

void SDBMS::ClassRoomData::SetStudentsData(const std::deque<SDBMS::StudentData> studData)
{
    m_studentData = studData;
}

std::deque<SDBMS::StudentData>::iterator SDBMS::ClassRoomData::FindStudent(int rollNumber)
{
    std::deque<SDBMS::StudentData>::iterator itr = m_studentData.end();

    for (auto i = m_studentData.begin(); i != m_studentData.end(); ++i)
    {
        if (i->GetRollNumber() == rollNumber)
        {
            itr = i;
        }
    }
    return itr;
}
