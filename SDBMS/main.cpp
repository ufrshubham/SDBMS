#include "SDBMS_BASE_CLASS.h"
#include "Menu.h"
#include "ClassRoomData.h"
#include <iostream>
#include "SDBMS_Utilities.h"
#include <deque>
#include <cctype>
#include <set>

SDBMS::MainMenuOptions MainMenu();
void AddNewClass();
void DeleteExisitingClass();
void InitGlobalDataManager();
std::set<std::deque<SDBMS::ClassRoomData>::iterator> ClassRoomLocator(std::set<int> deleteSet);

//This deque will be our doubly linked list which will store
//all the class room data. This will hold on to the data in current
//session untill exit is called.
std::deque<SDBMS::ClassRoomData> globalDataManager;

int main()
{
    InitGlobalDataManager();

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
            DeleteExisitingClass();
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
    std::deque<SDBMS::StudentData> studentDataList;

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

    //Push this classRoomData into out globalDataManager
    globalDataManager.push_back(classRoomData);

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "New class room data added succesfully" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
}

//used to delete exisiting class room data from globalDataManager
void DeleteExisitingClass()
{
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Deleting an existing class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    std::string deleteClassRoomNumber;
    std::set<int> deleteSet;
    char choice;

    //Get class room numbers from user to be deleted
    //Here I am getting it in the form of a string to allow
    //deleting of multiple class room records at once
    std::cout << "Enter class room number to delete: " << std::endl;
    std::getline(std::cin, deleteClassRoomNumber);

    //This loop is written to seperate out class room numbers for
    //user provided input seperated by blank space
    for (int i = 0, j = 0; i < deleteClassRoomNumber.length(); ++i)
    {
        if (std::isdigit(deleteClassRoomNumber[i]))
        {
            continue;
        }
        else if (deleteClassRoomNumber[i] != ' ' || deleteClassRoomNumber[i] != '\n')
        {
            deleteSet.insert(std::stoi(deleteClassRoomNumber.substr(j,i-j)));
            j = i;
        }
    }

    auto itrList = ClassRoomLocator(deleteSet);

    std::cout << "Are you sure you want to delete these " << itrList.size() << " class room data(y/n)?" << std::endl;
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        //Loop over the iterators to be deleted and pass them to globalDataManager's erase function
        for (auto &i : itrList)
        {
            globalDataManager.erase(i);
        }
    }
}

void InitGlobalDataManager()
{
    //Will be implemented later. This function will read the binary file that we will store
    //and then will filling the data from it into globalDataManager
}

//This function will traverse through the globalDataManager and find the desired class room number
//Then it will return the iterators to those class room data in globalDataManager
std::set<std::deque<SDBMS::ClassRoomData>::iterator> ClassRoomLocator(std::set<int> deleteSet)
{
    std::set<std::deque<SDBMS::ClassRoomData>::iterator> itrList;

    //Traverse through all the members of globalDataManager
    for (auto itr = globalDataManager.begin(); itr != globalDataManager.end(); ++itr)
    {
        //if class room number of current class room data in globalDataManager is
        //also found in deleteSet then count will return 1. 
        if (deleteSet.count(itr->GetClassRoomNumber()))
        {
            //as the class room number is found in deleteSet we will store the
            //iterator in itrList
            itrList.insert(itr);
        }
    }

    return itrList;
}
