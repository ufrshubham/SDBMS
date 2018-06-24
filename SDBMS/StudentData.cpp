#include "StudentData.h"



SDBMS::StudentData::StudentData()
{
    m_marks = { 0 };
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

SDBMS::subjectMarks SDBMS::StudentData::GetSubjectMarks()
{
    subjectMarks subMarks{ 
                           m_marks.mEnglish,
                           m_marks.mPhysics,
                           m_marks.mChemistry,
                           m_marks.mMaths,
                           m_marks.mCompSci
                         };
    return subMarks;
}

void SDBMS::StudentData::SetSubjectMarks(const subjectMarks subMarks)
{
    m_marks = subMarks;
}
