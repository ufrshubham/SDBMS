//This file contains the ClassRoomData class.

#pragma once

#include "SDBMS_BASE_CLASS.h"
#include "StudentData.h"
#include <vector>

namespace SDBMS
{
    class ClassRoomData :
        public SDBMS_BASE_CLASS
    {
        int m_classRoomNumber;                  //stores the class room number
        int m_numberOfStudents;                 //stores the number of student in this class room
        std::vector<StudentData> m_studentData; //stores the record of all the students in this class room
    public:
        ClassRoomData();
        ~ClassRoomData();

        int GetClassRoomNumber();           //used to get the class room number
        void SetClassRoomNumber(const int); //used to set the class room number

        int GetNumberOfStudents();           //used to get the number of students in this class room
        void SetNumberOfStudents(const int); //used to set the number of students in this class room

        std::vector<StudentData> GetStudentsData();           //used to get the data of all the students in this class room
        void SetStudentsData(const std::vector<StudentData>); //used to set the data of all the students in this class room
    };
}

