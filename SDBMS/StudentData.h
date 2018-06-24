#pragma once
#include "SDBMS_BASE_CLASS.h"
#include<string>

namespace SDBMS
{
    struct subjectMarks
    {
        int mEnglish;
        int mPhysics;
        int mChemistry;
        int mMaths;
        int mCompSci;
    };

    class StudentData :
        public SDBMS_BASE_CLASS
    {
        static int m_rollNumber;
        std::string m_name;
        subjectMarks m_marks;

    public:
        StudentData(bool init = false);
        ~StudentData();

        std::string GetName();
        void SetName(const std::string);

        subjectMarks GetSubjectMarks();
        void SetSubjectMarks(const subjectMarks);

        void FillStudentData();
    };
}

