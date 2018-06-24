//This file contains StudentData class. This class is used for storing data of a single student.

#pragma once

#include "SDBMS_BASE_CLASS.h"
#include<string>
#include "SubjectMarks.h"

namespace SDBMS
{
    class StudentData :
        public SDBMS_BASE_CLASS
    {
        int m_rollNumber;        //stores the roll number of current student
        std::string m_name;      //stores the name of current student
        SubjectMarks m_marks;    //stores the marks of all subjects of current student

    public:
        StudentData(bool init = false); //constructor with flag to tell is input is to be taken from console
        ~StudentData();

        std::string GetName();           //used to get the name of current student
        void SetName(const std::string); //used to set the name of current student

        SubjectMarks GetSubjectMarks();           //used to get all subject marks of current student
        void SetSubjectMarks(const SubjectMarks); //used to set all subject marks of current student

        void FillStudentData(); //used to get data from console
    };
}

