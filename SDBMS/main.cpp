#include "SDBMS_BASE_CLASS.h"
#include "Menu.h"
#include "ClassRoomData.h"
#include <iostream>

int MainMenu();
void AddNewClass();

int main()
{
    int choice = MainMenu();

    switch (choice)
    {
    case 1:
        AddNewClass();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    }

    return 0;
}

int MainMenu()
{
    SDBMS::Menu mainMenu;

    std::vector<std::string> optionsList;

    optionsList.push_back("Add new class room");
    optionsList.push_back("Edit existing class room");
    optionsList.push_back("Delete existing class room");
    optionsList.push_back("Save");
    optionsList.push_back("Save and Exit");
    optionsList.push_back("Exit without saving");

    mainMenu.SetOptionsList(optionsList);
    mainMenu.SetMenuName("Main Menu");
    mainMenu.DisplayMenu();

    return mainMenu.GetChoice();
}

void AddNewClass()
{
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Adding new class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    SDBMS::ClassRoomData classRoomData;
    std::vector<SDBMS::StudentData> studentDataList;

    int classRoomNumber,
        numberOfStudents;

    char addStudentData;

    std::cout << "Enter ClassRoom number: ";
    std::cin >> classRoomNumber;

    std::cout << "Enter number of students: ";
    std::cin >> numberOfStudents;

    classRoomData.SetClassRoomNumber(classRoomNumber);
    classRoomData.SetNumberOfStudents(numberOfStudents);

    std::cout << "Do you want to add student data now(y/n)?";
    std::cin >> addStudentData;

    if (addStudentData == 'y' || addStudentData == 'Y')
    {
        for (int i = 0; i < numberOfStudents; ++i)
        {
            studentDataList.push_back(SDBMS::StudentData(true));
        }

        classRoomData.SetStudentsData(studentDataList);
    }

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "New class room data added succesfully" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
}
