#pragma once
#include "SDBMS_BASE_CLASS.h"
#include <string>
#include <vector>

namespace SDBMS
{
    class Menu :
        public SDBMS_BASE_CLASS
    {
        int m_choice;
        bool m_isValidToCreate;
        std::string m_menuName;
        std::vector<std::string> m_optionsList;

        void CheckValidity();

    public:
        Menu();
        ~Menu();

        std::string GetOptionsList();
        void SetOptionsList(const std::vector<std::string>);

        std::string GetMenuName();
        void SetMenuName(const std::string);

        void DisplayMenu();
        int GetChoice();
    };
}

