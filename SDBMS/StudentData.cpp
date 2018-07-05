#include "StudentData.h"
#include <iostream>
#include "SubjectMarks.h"
#include <iomanip>

#define INT_LENGTH(X) std::string(std::to_string(X)).length()

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

SDBMS::SubjectMarks* SDBMS::StudentData::GetSubjectMarks()
{
    return &m_marks;
}

void SDBMS::StudentData::SetSubjectMarks(const SDBMS::SubjectMarks subMarks)
{
    m_marks = subMarks;
}

void SDBMS::StudentData::FillStudentData()
{
    SDBMS::SubjectMarks subMarks = { 0 };

    std::cout << "\tStudent " << m_rollNumber << " name: ";
    std::cin.ignore();
    std::getline(std::cin, m_name);

    std::cout << "\tEnter marks:" << std::endl;
    std::cout << "\t\tEnglish: ";
    std::cin >> subMarks.mEnglish;

    std::cout << "\t\tPhysics: ";
    std::cin >> subMarks.mPhysics;

    std::cout << "\t\tChemistry: ";
    std::cin >> subMarks.mChemistry;

    std::cout << "\t\tMaths: ";
    std::cin >> subMarks.mMaths;

    std::cout << "\t\tComputer Science: ";
    std::cin >> subMarks.mCompSci;

    SetSubjectMarks(subMarks);
}

void SDBMS::StudentData::ShowStudentData()
{
    std::cout << m_rollNumber << std::setw(11) << m_name << std::setw(20 - m_name.length())
              << m_marks.mEnglish <<std::setw(5- INT_LENGTH(m_marks.mEnglish))<< m_marks.mPhysics<< std::setw(5 - INT_LENGTH(m_marks.mPhysics))
              << m_marks.mChemistry << std::setw(6 - INT_LENGTH(m_marks.mChemistry)) << m_marks.mMaths << std::setw(7- INT_LENGTH(m_marks.mMaths))
              << m_marks.mCompSci << std::endl;
}
