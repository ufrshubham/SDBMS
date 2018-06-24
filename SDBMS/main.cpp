#include "SDBMS_BASE_CLASS.h"
#include "Menu.h"
#include "ClassRoomData.h"
#include <iostream>
#include "SDBMS_Utilities.h"
#include <deque>
#include <cctype>
#include <set>
#include <algorithm>

SDBMS::MainMenuOptions MainMenu();
SDBMS::EditMenuOptions EditMenu();

void AddNewClass();
void EditExisitingClass();
void DeleteExisitingClass();
void AddNewStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr);
void InitGlobalDataManager();
std::set<std::deque<SDBMS::ClassRoomData>::iterator> ClassRoomLocator(std::vector<int> deleteVector);

//This deque will be our doubly linked list which will store
//all the class room data. This will hold on to the data in current
//session untill exit is called.
std::deque<SDBMS::ClassRoomData> globalDataManager;

int main()
{
    InitGlobalDataManager();

    SDBMS::MainMenuOptions choice = SDBMS::Exit_No_Save;

    //Keep going untill user enters invalid choice
    while (choice != SDBMS::MainMenu_Invalid_Choice)
    {
        choice = MainMenu();

        switch (choice)
        {
        case SDBMS::Add_Class_Data:
            AddNewClass();
            break;
        case SDBMS::Edit_Class_Data:
            EditExisitingClass();
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
            choice = SDBMS::MainMenu_Invalid_Choice;
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

SDBMS::EditMenuOptions EditMenu()
{
    SDBMS::Menu editMenu;

    std::vector<std::string> optionsList;

    optionsList.push_back("Add new student data");
    optionsList.push_back("Edit existing student data");
    optionsList.push_back("Delete exisiting student data");
    optionsList.push_back("Edit");

    editMenu.SetOptionsList(optionsList);
    editMenu.SetMenuName("Edit Menu");
    editMenu.DisplayMenu();

    return static_cast<SDBMS::EditMenuOptions>(editMenu.GetChoice());
}

//used to create a new class object
void AddNewClass()
{
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Adding new class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    int classRoomNumber,
        numberOfStudents;

    char addStudentData;

    std::cout << "Enter ClassRoom number: ";
    std::cin >> classRoomNumber;

    std::cout << "Enter number of students: ";
    std::cin >> numberOfStudents;

    //This will create classRoomData and will set the class room number 
    //and number of students to values provided by user.
    SDBMS::ClassRoomData classRoomData(classRoomNumber, numberOfStudents);

    //Ask user if he wants to enter data of user right now. This is done 
    //because users can choose to first add dummy class room and later use 
    //Edit class room data option to add student data to it.
    std::cout << "Do you want to add student data now(y/n)?";
    std::cin >> addStudentData;

    if (addStudentData == 'y' || addStudentData == 'Y')
    {
        //Since we have already initialized classRoomData with classRoomNumber and numberOfStudents,
        //as well as m_studentData inside classRoomData is also initialized with class room number and
        //roll numbers, here we just have to get name and subject marks of each student.
        //So here, classRoomData.GetStudentsData() will return the m_studentData deque stored in classRoomData
        //and we will loop over it and call FillStudentData() for each of it's element
        for (auto itr = classRoomData.GetStudentsData()->begin(); itr != classRoomData.GetStudentsData()->end(); ++itr)
        {
            itr->FillStudentData();
        }
    }

    //Push this classRoomData into out globalDataManager
    globalDataManager.push_back(classRoomData);

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "New class room data added succesfully" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
}

void EditExisitingClass()
{
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Editing existing class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    int classRoomNumberToEdit = 0;

    std::cout << "Enter class room number to edit: " << std::endl;
    std::cin >> classRoomNumberToEdit;

    auto itrList = ClassRoomLocator(std::vector<int>(1, classRoomNumberToEdit));

    //If the itrList is empty that means we did not find the data
    if (!itrList.empty())
    {
        SDBMS::EditMenuOptions choice = SDBMS::Exit;

        choice = EditMenu();

        while (choice != SDBMS::Edit_Invalid_Choice)
        {
            switch (choice)
            {
            case SDBMS::Add_Student_Data:
                AddNewStudentData(itrList);
                choice = SDBMS::Edit_Invalid_Choice;
                break;
            case SDBMS::Edit_Student_Data:
                break;
            case SDBMS::Delete_Student_Data:
                break;
            case SDBMS::Exit:
                break;
            default:
                choice = SDBMS::Edit_Invalid_Choice;
                break;
            }
        }
    }
    else
    {
        std::cout << "Invalid class room entered. Returing to Main Menu." << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------" << std::endl;
}

//used to delete exisiting class room data from globalDataManager
void DeleteExisitingClass()
{
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Deleting an existing class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    std::string deleteClassRoomNumber;
    std::vector<int> deleteVector;
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
            deleteVector.push_back(std::stoi(deleteClassRoomNumber.substr(j,i-j)));
            j = i;
        }
    }

    auto itrList = ClassRoomLocator(deleteVector);

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

//Adds a new student data to the current class room
void AddNewStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr)
{
    //Since we allow addition of a new student to a single class room at a time
    //we can be sure that classRoomItr set will have only one iterator in it.
    //This iterator will be located at the begining. So we get pointer to current 
    //class from set of iterator
    auto currentClassRoom = *classRoomItr.begin();

    int currentRollNumber = currentClassRoom->GetMaxRollNumber();
    int currentClassRoomNumber = currentClassRoom->GetClassRoomNumber();
    
    //We will construct a newStudent using currentClassRoomNumber and 1+currentRollNumber
    SDBMS::StudentData newStudent(currentClassRoomNumber, ++currentRollNumber);

    //Calling FillStudentData() on newStudent so that we can get the name and marks
    newStudent.FillStudentData();

    //Push back this newStudent in m_studentData deque stored in currentClassRoom
    //Also increment the number of students and max roll number in currentClassRoom by 1
    currentClassRoom->GetStudentsData()->push_back(newStudent);
    currentClassRoom->SetNumberOfStudents(currentClassRoom->GetNumberOfStudents() + 1);
    currentClassRoom->SetMaxRollNumber(currentClassRoom->GetMaxRollNumber() + 1);
}

void InitGlobalDataManager()
{
    //Will be implemented later. This function will read the binary file that we will store
    //and then will filling the data from it into globalDataManager
}

//This function will traverse through the globalDataManager and find the desired class room number
//Then it will return the iterators to those class room data in globalDataManager
std::set<std::deque<SDBMS::ClassRoomData>::iterator> ClassRoomLocator(std::vector<int> deleteVector)
{
    std::set<std::deque<SDBMS::ClassRoomData>::iterator> itrList;

    //Traverse through all the members of globalDataManager
    for (auto itr = globalDataManager.begin(); itr != globalDataManager.end(); ++itr)
    {
        //if class room number of current class room data in globalDataManager is
        //also found in deleteVector then insert it in itrList. 
        if (std::find(deleteVector.begin(), deleteVector.end(), itr->GetClassRoomNumber()) != deleteVector.end())
        {
            //as the class room number is found in deleteVector we will store the iterator in itrList
            itrList.insert(itr);
        }
    }

    return itrList;
}
