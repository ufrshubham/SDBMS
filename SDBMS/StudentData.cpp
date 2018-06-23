#include "StudentData.h"



StudentData::StudentData()
{
    m_marks = { 0 };
}


StudentData::~StudentData()
{
}

std::string StudentData::GetName()
{
    return m_name;
}

void StudentData::SetName(const std::string name)
{
    m_name = name;
}

subjectMarks StudentData::GetSubjectMarks()
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

void StudentData::SetSubjectMarks(const subjectMarks subMarks)
{
    m_marks = subMarks;
}
