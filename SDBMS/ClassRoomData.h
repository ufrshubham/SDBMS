#pragma once
#include "SDBMS_BASE_CLASS.h"
#include "StudentData.h"
#include <vector>

namespace SDBMS
{
    class ClassRoomData :
        public SDBMS_BASE_CLASS
    {
        int m_classRoomNumber;
        int m_numberOfStudents;
        std::vector<StudentData> m_studentData;
    public:
        ClassRoomData();
        ~ClassRoomData();

        int GetClassRoomNumber();
        void SetClassRoomNumber(const int);

        int GetNumberOfStudents();
        void SetNumberOfStudents(const int);

        std::vector<StudentData> GetStudentsData();
        void SetStudentsData(const std::vector<StudentData>);
    };
}

