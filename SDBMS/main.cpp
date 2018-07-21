#include "SDBMS_BASE_CLASS.h"
#include "Menu.h"
#include "ClassRoomData.h"
#include <iostream>
#include "SDBMS_Utilities.h"
#include <deque>
#include <cctype>
#include <set>
#include <algorithm>
#include <fstream>
#include "Logger.h"

SDBMS::MainMenuOptions MainMenu();
SDBMS::EditMenuOptions EditMenu(bool isMinimal);
SDBMS::EditStudentDataOptions EditStudentDataMenu();

void AddNewClass();
void ShowClassData();
void EditExisitingClass();
void DeleteExisitingClass();

std::vector<int> ExtractIntsFromString(const std::string &userInputString);

void AddNewStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr);
void EditExisitingStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr);
void DeleteExisitingStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr);
void SaveToFile();

void InitGlobalDataManager();
int GetNewMarks();
std::set<std::deque<SDBMS::ClassRoomData>::iterator> ClassRoomLocator(std::vector<int> deleteVector);

bool IsStringValid(std::string userInput);

//This deque will be our doubly linked list which will store
//all the class room data. This will hold on to the data in current
//session until exit is called.
std::deque<SDBMS::ClassRoomData> globalDataManager;

//Since we need logger in multiple functions here, creating a global object
SDBMS::Logger *logger = SDBMS::Logger::CreateLogger();

int main()
{
    *logger <<__FUNCTION__;

    SDBMS::MainMenuOptions choice = SDBMS::Exit_No_Save;

    //Keep going until user enters invalid choice
    while (choice != SDBMS::MainMenu_Invalid_Choice)
    {
        choice = MainMenu();

        switch (choice)
        {
        case SDBMS::Add_Class_Data:
            AddNewClass();
            break;
        case SDBMS::Show_Class_Data:
            ShowClassData();
            break;
        case SDBMS::Edit_Class_Data:
            EditExisitingClass();
            break;
        case SDBMS::Delete_Class_Data:
            DeleteExisitingClass();
            break;
        case SDBMS::Save:
            //SaveToFile();
            break;
        case SDBMS::Save_Exit:
            break;
        case SDBMS::Exit_No_Save:
            choice = SDBMS::MainMenu_Invalid_Choice;
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
    *logger <<__FUNCTION__;

    SDBMS::Menu mainMenu;

    std::vector<std::string> optionsList;

    optionsList.push_back("Add new class room");

    //If class room data does not exist, no point in showing extra options.
    if (!globalDataManager.empty())
    {
        optionsList.push_back("Show class room data");
        optionsList.push_back("Edit existing class room");
        optionsList.push_back("Delete existing class room");
        optionsList.push_back("Save");
        optionsList.push_back("Save and Exit");
    }
    optionsList.push_back("Exit");

    mainMenu.SetOptionsList(optionsList);
    mainMenu.SetMenuName("Main Menu");
    mainMenu.DisplayMenu();

    // This part of code is written to fix the issue of Exit. When we First time run the program
    // and select exit option it was not working . It was diaplaying the Show class data option.
    if ((globalDataManager.empty()) && (mainMenu.GetChoice() == 2))
    {
        mainMenu.SetChoice(SDBMS::MainMenuOptions::Exit_No_Save);
    }

    return static_cast<SDBMS::MainMenuOptions>(mainMenu.GetChoice());
}

SDBMS::EditMenuOptions EditMenu(bool isMinimal)
{
    *logger <<__FUNCTION__;

    SDBMS::Menu editMenu;

    std::vector<std::string> optionsList;

    optionsList.push_back("Add new student data");

    //No need to show these option if student data does not exist
    if (!isMinimal)
    {
        optionsList.push_back("Edit existing student data");
        optionsList.push_back("Delete existing student data");
    }

    optionsList.push_back("Exit");

    editMenu.SetOptionsList(optionsList);
    editMenu.SetMenuName("Edit Menu");
    editMenu.DisplayMenu();

    return static_cast<SDBMS::EditMenuOptions>(editMenu.GetChoice());
}

SDBMS::EditStudentDataOptions EditStudentDataMenu()
{
    *logger <<__FUNCTION__;

    SDBMS::Menu editStudentDataMenu;

    std::vector<std::string> optionsList;

    optionsList.push_back("Edit name");
    optionsList.push_back("Edit English marks");
    optionsList.push_back("Edit Physics marks");
    optionsList.push_back("Edit Chemistry marks");
    optionsList.push_back("Edit Maths marks");
    optionsList.push_back("Edit Computer Science marks");


    editStudentDataMenu.SetOptionsList(optionsList);
    editStudentDataMenu.SetMenuName("Edit Student Data Menu");
    editStudentDataMenu.DisplayMenu();

    return static_cast<SDBMS::EditStudentDataOptions>(editStudentDataMenu.GetChoice());
}

//used to create a new class object
void AddNewClass()
{
    *logger <<__FUNCTION__;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Adding new class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    int classRoomNumber,
        numberOfStudents;

    char addStudentData;

    std::cout << "Enter class room number: ";
    std::cin >> classRoomNumber;

    //Don't allow negative values
    if (classRoomNumber > 0)
    {
        //We need to perform a validation check to ensure that user does not try to create 
        //an existing class
        bool matchFound = false;

        for (auto &itr : globalDataManager)
        {
            if (itr.GetClassRoomNumber() == classRoomNumber)
            {
                matchFound = true;
            }
        }

        if (!matchFound)
        {
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

            //Push this classRoomData into our globalDataManager
            globalDataManager.push_back(classRoomData);

            std::cout << "-------------------------------------------------------------------------" << std::endl;
            std::cout << "New class room data added succesfully" << std::endl;
        }
        else
        {
            std::cout << "-------------------------------------------------------------------------" << std::endl;
            std::cout << "This class already exisits." << std::endl;
        }
    }
    else
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << "Invalid class room number entered!" << std::endl;
    }
}

void ShowClassData()
{
    *logger <<__FUNCTION__;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Showing class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    int classRoomNumber = 0;

    std::cout << "Enter class room number: ";
    std::cin >> classRoomNumber;

    if (classRoomNumber > 0)
    {
        auto itrList = ClassRoomLocator(std::vector<int>(1, classRoomNumber));

        //Added check to see if the entered class room number is valid or not
        if (!itrList.empty())
        {
            for (auto &itr : itrList)
            {
                std::cout << "Class Room Number: " << itr->GetClassRoomNumber();
                std::cout << " Number of student: " << itr->GetNumberOfStudents() << std::endl;
                std::cout << "Roll No.   Name               Eng Phy Chem Maths Comp" << std::endl;

                auto sdItr = itr->GetStudentsData();

                for (auto i = sdItr->begin(); i != sdItr->end(); ++i)
                {
                    i->ShowStudentData();
                }
            }
        }
        else
        {
            std::cout << "-------------------------------------------------------------------------" << std::endl;
            std::cout << "Such class room does not exist!" << std::endl;
        }
    }
    else
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << "Invalid class room number entered!" << std::endl;
    }
}

void EditExisitingClass()
{
    *logger <<__FUNCTION__;

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
        bool isMinimal = true;

        auto currentClassRoom = *itrList.begin();
        int numberOfStudents = currentClassRoom->GetNumberOfStudents();

        if (numberOfStudents > 0)
        {
            isMinimal = false;
        }

        while (choice != SDBMS::Edit_Invalid_Choice)
        {
            choice = EditMenu(isMinimal);

            switch (choice)
            {
            case SDBMS::Add_Student_Data:
                AddNewStudentData(itrList);
                break;
            case SDBMS::Edit_Student_Data:
                EditExisitingStudentData(itrList);
                break;
            case SDBMS::Delete_Student_Data:
                DeleteExisitingStudentData(itrList);
                break;
            case SDBMS::Exit:
                choice = SDBMS::Edit_Invalid_Choice;
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
}

//used to delete exisiting class room data from globalDataManager
void DeleteExisitingClass()
{
    *logger <<__FUNCTION__;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Deleting an existing class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    std::string userInput;
    std::vector<int> deleteClassRoomList(0, 0);
    char choice;

    //Get class room numbers from user to be deleted
    //Here I am getting it in the form of a string to allow
    //deleting of multiple class room records at once
    std::cout << "Enter class room number to delete: ";
    std::cin.ignore();
    std::getline(std::cin, userInput);

    deleteClassRoomList = ExtractIntsFromString(userInput);

    //If string could not be parsed, it means that some invalid character was entred by user.
    if (!deleteClassRoomList.empty())
    {
        auto itrList = ClassRoomLocator(deleteClassRoomList);

        //If itrList is empty, that means that we could not find the class rooms in globalDataManager
        if (!itrList.empty())
        {
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
        else
        {
            std::cout << "-------------------------------------------------------------------------" << std::endl;
            std::cout << "Such class room does not exist!" << std::endl;
        }
    }
    else
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << "Invalid input!" << std::endl;
    }
}

//Adds a new student data to the current class room
void AddNewStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr)
{
    *logger <<__FUNCTION__;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Adding new student data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    //Since we allow editing of a single class room at a time
    //we can be sure that classRoomItr set will have only one iterator in it.
    //This iterator will be located at the begining. So we get pointer to current 
    //class room from set of iterator
    auto currentClassRoom = *classRoomItr.begin();

    int currentRollNumber = currentClassRoom->GetMaxRollNumber();
    int currentClassRoomNumber = currentClassRoom->GetClassRoomNumber();

    // If a class has unused roll number then in that case if we are adding new student 
    // then it should use unused roll number .
    // It should traverse the list from starting to the MaxRollNumber
    // and if gets any unused no in between this , then that no should be assigned to new student

    bool foundUnusedRollNumber = false;
    for (int i = 1; i <= currentRollNumber; i++)
    {
        auto itrStud = currentClassRoom->FindStudent(i);
        if (itrStud == currentClassRoom->GetStudentsData()->end())
        {
            currentRollNumber = i;
            foundUnusedRollNumber = true;
            break;
        }
    }

    if (foundUnusedRollNumber == false)
    {
        ++currentRollNumber;
    }

    //We will construct a newStudent using currentClassRoomNumber and currentRollNumber
    SDBMS::StudentData newStudent(currentClassRoomNumber, currentRollNumber);

    //Calling FillStudentData() on newStudent so that we can get the name and marks
    newStudent.FillStudentData();

    //Push back this newStudent in m_studentData deque stored in currentClassRoom
    //Also increment the number of students and max roll number in currentClassRoom by 1
    currentClassRoom->GetStudentsData()->push_back(newStudent);
    currentClassRoom->SetNumberOfStudents(currentClassRoom->GetNumberOfStudents() + 1);
    currentClassRoom->SetMaxRollNumber(currentClassRoom->GetMaxRollNumber() + 1);
}

//Edits data of an existing student from a class
void EditExisitingStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr)
{
    *logger <<__FUNCTION__;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Editing existing student data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    int rollNumberToEdit = 0;
    SDBMS::EditStudentDataOptions choice = SDBMS::Edit_Name;

    //Since we allow editing of a single class room at a time
    //we can be sure that classRoomItr set will have only one iterator in it.
    //This iterator will be located at the begining. So we get pointer to current 
    //class room from set of iterator
    auto currentClassRoom = *classRoomItr.begin();

    //Display data in current class room to user
    std::cout << "Class Room Number: " << currentClassRoom->GetClassRoomNumber() << std::endl;
    std::cout << "Student Data: " << std::endl;

    auto studentsData = currentClassRoom->GetStudentsData();
    for (auto itr = studentsData->begin(); itr != studentsData->end(); ++itr)
    {
        std::cout << "\t" << itr->GetRollNumber() << " " << itr->GetName() << std::endl;
    }

    //Take input roll number from user
    std::cout << "Enter roll number of student whose data is to be edited: ";
    std::cin >> rollNumberToEdit;

    //Search this roll number in currentClassRoom's m_studentData deque using FindStudent()
    auto itr = currentClassRoom->FindStudent(rollNumberToEdit);

    //If user enters invaild roll number we might not find it in m_studentData
    if (itr != currentClassRoom->GetStudentsData()->end())
    {
        //Show student edit menu and get choice
        choice = EditStudentDataMenu();

        while (choice != SDBMS::Edit_Student_Data_Invalid)
        {
            std::string newName = "";

            switch (choice)
            {
            case SDBMS::Edit_Name:
                std::cout << "Enter new name: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                itr->SetName(newName);
                std::cout << "Edit Successful" << std::endl;
                choice = SDBMS::Edit_Student_Data_Invalid;
                break;

            case SDBMS::Edit_Eng:
                itr->GetSubjectMarks()->mEnglish = GetNewMarks();
                std::cout << "Edit Successful" << std::endl;
                choice = SDBMS::Edit_Student_Data_Invalid;
                break;

            case SDBMS::Edit_Phy:
                itr->GetSubjectMarks()->mPhysics = GetNewMarks();
                std::cout << "Edit Successful" << std::endl;
                choice = SDBMS::Edit_Student_Data_Invalid;
                break;

            case SDBMS::Edit_Chem:
                itr->GetSubjectMarks()->mChemistry = GetNewMarks();
                std::cout << "Edit Successful" << std::endl;
                choice = SDBMS::Edit_Student_Data_Invalid;
                break;

            case SDBMS::Edit_Math:
                itr->GetSubjectMarks()->mMaths = GetNewMarks();
                std::cout << "Edit Successful" << std::endl;
                choice = SDBMS::Edit_Student_Data_Invalid;
                break;

            case SDBMS::Edit_CompSci:
                itr->GetSubjectMarks()->mCompSci = GetNewMarks();
                std::cout << "Edit Successful" << std::endl;
                choice = SDBMS::Edit_Student_Data_Invalid;
                break;

            default:
                choice = SDBMS::Edit_Student_Data_Invalid;
                break;
            }
        }
    }
}

//Delete data of an existing student from a class
void DeleteExisitingStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr)
{
    *logger <<__FUNCTION__;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Deleteing existing student data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    std::string userInputString = "";
    char choice = 'y';

    std::cout << "Enter roll numbers of students to be deleted: ";
    std::cin.ignore();
    std::getline(std::cin, userInputString);

    std::vector<int> deleteRollNumberList = ExtractIntsFromString(userInputString);
    std::set<std::deque<SDBMS::StudentData>::iterator> deleteItrList;

    //Since we allow editing of a single class room at a time
    //we can be sure that classRoomItr set will have only one iterator in it.
    //This iterator will be located at the begining. So we get pointer to current 
    //class room from set of iterator
    auto currentClassRoom = *classRoomItr.begin();
    auto currentStudentsData = currentClassRoom->GetStudentsData();
    std::deque<SDBMS::StudentData> newStudentData;
    int deleteCount = 0;

    //In this loop we will copy all the elements from currentStudentsData to newStudentData
    //except the ones which user wants to delete.
    for (auto itr = currentStudentsData->begin(); itr != currentStudentsData->end(); ++itr)
    {
        //If not found, copy in newStudentData
        if (std::find(deleteRollNumberList.begin(), deleteRollNumberList.end(), itr->GetRollNumber()) == deleteRollNumberList.end())
        {
            newStudentData.push_back(*itr);
        }
        //Else increment the delete count
        else
        {
            ++deleteCount;
        }
    }

    std::cout << "Are you sure you want to delete these " << deleteCount << " student data(y/n) ?";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        //Set the newStudentData in currentClassRoom
        currentClassRoom->SetStudentsData(newStudentData);

        //Also update the number of students in class after deletion
        currentClassRoom->SetNumberOfStudents(currentClassRoom->GetNumberOfStudents() - deleteCount);
        currentClassRoom->SetMaxRollNumber(currentClassRoom->GetMaxRollNumber() - deleteCount);
    }
}

//Saves the current state of globalDataManager to a binary file
void SaveToFile()
{
    *logger <<__FUNCTION__;

    std::string fileName("savfile.sdbms");
    std::ofstream dataFile;
    dataFile.open(fileName, std::ios::binary);

    if (dataFile.is_open())
    {
        char* classData = nullptr;

        for (auto itr : globalDataManager)
        {
            classData = reinterpret_cast<char*>(new SDBMS::ClassRoomData(itr));

            dataFile.write(classData, sizeof(SDBMS::ClassRoomData));
        }
        delete[] classData;
    }
    else
    {
        std::cout << "Could not save." << std::endl;
    }
    dataFile.close();
}

void InitGlobalDataManager()
{
    *logger <<__FUNCTION__;

    //This function will read the saved file that we saved on disk,
    //and then will filling the data from it into globalDataManager

    std::string fileName("savfile.sdbms");
    std::ifstream dataFile;
    dataFile.open(fileName, std::ios::binary);

    if (dataFile.is_open())
    {
        char* classData = new char[sizeof(SDBMS::ClassRoomData)];

        while (!dataFile.eof())
        {
            dataFile.read(classData, sizeof(SDBMS::ClassRoomData));

            //globalDataManager.push_back(*(reinterpret_cast<SDBMS::ClassRoomData*>(classData)));
        }

        delete[] classData;
    }
    else
    {
        std::cout << "Could not load data." << std::endl;
    }
    dataFile.close();
}

int GetNewMarks()
{
    *logger <<__FUNCTION__;

    int newMarks = 0;
    std::cout << "Enter new marks: ";
    std::cin >> newMarks;
    return newMarks;
}

//This function will traverse through the globalDataManager and find the desired class room number
//Then it will return the iterators to those class room data in globalDataManager
std::set<std::deque<SDBMS::ClassRoomData>::iterator> ClassRoomLocator(std::vector<int> deleteVector)
{
    *logger <<__FUNCTION__;

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

bool IsStringValid(std::string userInput)
{
    *logger <<__FUNCTION__;

    bool isValid = true;

    for (auto &ch : userInput)
    {
        if (!std::isdigit(ch) && ch != ' ' && ch != '\n')
        {
            isValid = false;
            break;
        }
    }
    return isValid;
}

std::vector<int> ExtractIntsFromString(const std::string &userInputString)
{
    *logger <<__FUNCTION__;

    std::vector<int> intsVector(0, 0);

    if (IsStringValid(userInputString))
    {
        //This loop is written to seperate out integers from user provided input seperated by blank space
        for (int i = 0, j = 0; i < userInputString.length() + 1; ++i)
        {
            if (std::isdigit(userInputString[i]))
            {
                continue;
            }
            else if (userInputString[i] != ' ' || userInputString[i] != '\n')
            {
                intsVector.push_back(std::stoi(userInputString.substr(j, i - j)));
                j = i;
            }
        }
    }
    return intsVector;
}
