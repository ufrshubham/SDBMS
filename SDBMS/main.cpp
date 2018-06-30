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
SDBMS::EditMenuOptions EditMenu();
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

//This deque will be our doubly linked list which will store
//all the class room data. This will hold on to the data in current
//session until exit is called.
std::deque<SDBMS::ClassRoomData> globalDataManager;

int main()
{
    SDBMS::MainMenuOptions choice = SDBMS::Exit_No_Save;
    //try
    //{
    //    InitGlobalDataManager();
    //}
    //catch (...)
    //{
    //    SDBMS::Logger *log = SDBMS::Logger::CreateLogger();

    //    if (log != nullptr)
    //    {
    //        *log << "Exception caught. Could not load data from file. \nProgram is now terminating.";
    //    }

    //    choice = SDBMS::MainMenu_Invalid_Choice;
    //}

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
    optionsList.push_back("Show class room data");
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

SDBMS::EditStudentDataOptions EditStudentDataMenu()
{
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
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Adding new class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    int classRoomNumber,
        numberOfStudents;

    char addStudentData;

    std::cout << "Enter class room number: ";
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
}

void ShowClassData()
{
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Adding new class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    int classRoomNumber = 0;

    std::cout << "Enter class room number: ";
    std::cin >> classRoomNumber;

    auto itrList = ClassRoomLocator(std::vector<int>(1, classRoomNumber));

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
                EditExisitingStudentData(itrList);
                choice = SDBMS::Edit_Invalid_Choice;
                break;
            case SDBMS::Delete_Student_Data:
                DeleteExisitingStudentData(itrList);
                choice = SDBMS::Edit_Invalid_Choice;
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
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Deleting an existing class room data" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    std::string userInput;
    std::vector<int> deleteClassRoomList(0,0);
    char choice;

    //Get class room numbers from user to be deleted
    //Here I am getting it in the form of a string to allow
    //deleting of multiple class room records at once
    std::cout << "Enter class room number to delete: ";
    std::cin.ignore();
    std::getline(std::cin, userInput);

    deleteClassRoomList = ExtractIntsFromString(userInput);

    auto itrList = ClassRoomLocator(deleteClassRoomList);

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

//Edits data of an existing student from a class
void EditExisitingStudentData(std::set<std::deque<SDBMS::ClassRoomData>::iterator> classRoomItr)
{
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

    for (auto itr = currentStudentsData->begin(); itr != currentStudentsData->end(); ++itr)
    {
        if (std::find(deleteRollNumberList.begin(), deleteRollNumberList.end(), itr->GetRollNumber()) != deleteRollNumberList.end())
        {
            deleteItrList.insert(itr);
        }
    }

    std::cout << "Are you sure you want to delete these " << deleteItrList.size() << " student data(y/n) ?";
    std::cin >> choice;

    if(choice == 'y' || choice == 'Y')
    {
        for (auto &i : deleteItrList)
        {
            currentStudentsData->erase(i);
        }
    }
}

//Saves the current state of globalDataManager to a binary file
void SaveToFile()
{
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
    SDBMS::Logger *log = SDBMS::Logger::CreateLogger();

    if (log != nullptr)
    {
        *log << "Log file opened succesfully.";
    }
    //This function will read the saved file that we saved on disk,
    //and then will filling the data from it into globalDataManager

    std::string fileName("savfile.sdbms");
    std::ifstream dataFile;
    dataFile.open(fileName, std::ios::binary);

    if (dataFile.is_open())
    {
        char* classData = new char[sizeof(SDBMS::ClassRoomData)];

        while(!dataFile.eof())
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
    int newMarks = 0;
    std::cout << "Enter new marks: ";
    std::cin >> newMarks;
    return newMarks;
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

std::vector<int> ExtractIntsFromString(const std::string &userInputString)
{
    std::vector<int> intsVector(0, 0);

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

    return intsVector;
}
