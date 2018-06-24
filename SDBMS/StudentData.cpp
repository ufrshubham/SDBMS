#include "StudentData.h"
#include <iostream>
#include "SubjectMarks.h"

SDBMS::StudentData::StudentData(int classRoomNumber, int rollNumber) : m_classRoomNumber(classRoomNumber)
{
    m_marks = { 0 };
    m_rollNumber = rollNumber;
}


SDBMS::StudentData::~StudentData()
{
}

int SDBMS::StudentData::GetRollNumber()
{
    return m_rollNumber;
}

void SDBMS::StudentData::SetRollNumber(const int rollNumber)
{
    m_rollNumber = rollNumber;
}

std::string SDBMS::StudentData::GetName()
{
    return m_name;
}

void SDBMS::StudentData::SetName(const std::string name)
{
    m_name = name;
}

int SDBMS::StudentData::GetClassRoomNumer()
{
    return m_classRoomNumber;
}

void SDBMS::StudentData::SetClassRoomNumber(const int classRoomNumber)
{
    m_classRoomNumber = classRoomNumber;
}

SDBMS::SubjectMarks SDBMS::StudentData::GetSubjectMarks()
{
    SDBMS::SubjectMarks subMarks{ 
                                  m_marks.mEnglish,
                                  m_marks.mPhysics,
                                  m_marks.mChemistry,
                                  m_marks.mMaths,
                                  m_marks.mCompSci
                                };
    return subMarks;
}

void SDBMS::StudentData::SetSubjectMarks(const SDBMS::SubjectMarks subMarks)
{
    m_marks = subMarks;
}

void SDBMS::StudentData::FillStudentData()
{
    SDBMS::SubjectMarks subMarks = { 0 };

    std::cout << "Student " << m_rollNumber << " name: ";
    std::cin >> m_name;

    std::cout << "Enter marks:" << std::endl;
    std::cout << "English: ";
    std::cin >> subMarks.mEnglish;

    std::cout << "Physics: ";
    std::cin >> subMarks.mPhysics;

    std::cout << "Chemistry: ";
    std::cin >> subMarks.mChemistry;

    std::cout << "Maths: ";
    std::cin >> subMarks.mMaths;

    std::cout << "Computer Science: ";
    std::cin >> subMarks.mCompSci;

    SetSubjectMarks(subMarks);
}
