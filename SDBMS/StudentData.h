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
        int m_classRoomNumber;   //stores the class room number of current student
        std::string m_name;      //stores the name of current student
        SubjectMarks m_marks;    //stores the marks of all subjects of current student

    public:
        StudentData(int classRoomNumber, int rollNumber = 0); //used to construct and set the class room number of current student
        ~StudentData();

        int GetRollNumber();           //used to get the roll number of current student
        void SetRollNumber(const int); //used to set the roll number of current student

        std::string GetName();           //used to get the name of current student
        void SetName(const std::string); //used to set the name of current student

        int GetClassRoomNumer();           //used to get the class room number of current student
        void SetClassRoomNumber(const int); //used to set the class room number of current student

        SubjectMarks* GetSubjectMarks();           //used to get all subject marks of current student
        void SetSubjectMarks(const SubjectMarks); //used to set all subject marks of current student

        void FillStudentData(); //used to get data from console
    };
}

