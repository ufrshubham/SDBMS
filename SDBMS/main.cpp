#include "SDBMS_BASE_CLASS.h"
#include "Menu.h"
#include "ClassRoomData.h"
#include <iostream>
#include "SDBMS_Utilities.h"

SDBMS::MainMenuOptions MainMenu();
void AddNewClass();

int main()
{
    SDBMS::MainMenuOptions choice = SDBMS::Exit_No_Save;

    //Keep going untill user enters invalid choice
    while (choice != SDBMS::Invalid_Choice)
    {
        choice = MainMenu();

        switch (choice)
        {
        case SDBMS::Add_Class_Data:
            AddNewClass();
            break;
        case SDBMS::Edit_Class_Data:
            break;
        case SDBMS::Delete_Class_Data:
            break;
        case SDBMS::Save:
            break;
        case SDBMS::Save_Exit:
            break;
        case SDBMS::Exit_No_Save:
            break;
        default:
            choice = SDBMS::Invalid_Choice;
            break;
        }
    }

    return 0;
}

//creates object of Menu class, displays it and return user input
SDBMS::MainMenuOptions MainMenu()
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

    return static_cast<SDBMS::MainMenuOptions>(mainMenu.GetChoice());
}

//used to create a new class object
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

    //Ask user if he wants to enter data of user right now
    //This is done because users can choose to first add dummy
    //class room and later use Edit class room data option
    //to add student data to it.
    std::cout << "Do you want to add student data now(y/n)?";
    std::cin >> addStudentData;

    if (addStudentData == 'y' || addStudentData == 'Y')
    {
        //Push the student data into studentDataList
        for (int i = 0; i < numberOfStudents; ++i)
        {
            //Here we are calling StudentData's constructor by passing a true flag
            //This flag will tell the constructor to get data for construction from
            //console
            studentDataList.push_back(SDBMS::StudentData(true));
        }

        classRoomData.SetStudentsData(studentDataList);
    }

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "New class room data added succesfully" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
}
