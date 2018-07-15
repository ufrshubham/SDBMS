//This file contains Menu class. This class can be used for constructing Menus.

#pragma once

#include "SDBMS_BASE_CLASS.h"
#include <string>
#include <vector>

namespace SDBMS
{
    class Menu :
        public SDBMS_BASE_CLASS
    {
        int m_choice;                           //stores the input from user
        bool m_isValidToCreate;                 //stores the validity of current object
        std::string m_menuName;                 //stores the current menu title
        std::vector<std::string> m_optionsList; //stores the list of options for current menu

        //checks if the tile name and options list
        //is set or not and set m_isValidToCreate 
        //accordingly
        void CheckValidity();
		


    public:
        Menu();
        ~Menu();

        std::vector<std::string> GetOptionsList();           //used to get the options list
        void SetOptionsList(const std::vector<std::string>); //used to set the options list

        std::string GetMenuName();           //used to get the menu name
        void SetMenuName(const std::string); //used to set the menu name

        void DisplayMenu(); //used to display current menu on screen
        
        int GetChoice(); //used to get the option entered by user

		void SetChoice(int);
    };
}
