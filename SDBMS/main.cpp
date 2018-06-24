#include "SDBMS_BASE_CLASS.h"
#include "Menu.h"
#include "ClassRoomData.h"

int MainMenu();
void AddNewClass();

int main()
{
    int choice = MainMenu();

    switch (choice)
    {
    case 1:
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
    SDBMS::ClassRoomData classRoomData;
}
