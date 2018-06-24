#include "StudentData.h"
#include <iostream>
#include "SubjectMarks.h"

int SDBMS::StudentData::m_rollNumber = 0;

SDBMS::StudentData::StudentData(bool init)
{
    //increase roll number for every construction
    ++m_rollNumber;

    m_marks = { 0 };

    //if init is true get the data from console for construction
    if (init)
    {
        FillStudentData();
    }
}


SDBMS::StudentData::~StudentData()
{
}

std::string SDBMS::StudentData::GetName()
{
    return m_name;
}

void SDBMS::StudentData::SetName(const std::string name)
{
    m_name = name;
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
