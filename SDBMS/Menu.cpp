#include "Menu.h"
#include <iostream>


void SDBMS::Menu::CheckValidity()
{
    //Check is the optionsList and menuName are set or not
    if (!m_optionsList.empty() && (m_menuName.size() != 0))
    {
        m_isValidToCreate = true;

    }
}

SDBMS::Menu::Menu()
{
    //By default validaity of current object will be false
    //and choice will be set to 0
    m_isValidToCreate = false;
    m_choice = 0;
}


SDBMS::Menu::~Menu()
{
}

std::vector<std::string> SDBMS::Menu::GetOptionsList()
{
    return m_optionsList;
}

void SDBMS::Menu::SetOptionsList(const std::vector<std::string> optionsList)
{
    m_optionsList = optionsList;
}

std::string SDBMS::Menu::GetMenuName()
{
    return m_menuName;
}

void SDBMS::Menu::SetMenuName(const std::string menuName)
{
    m_menuName = menuName;
}

void SDBMS::Menu::DisplayMenu()
{
    //First check validity of current menu object.
    //This will set the m_isValidToCreate accordingly
    CheckValidity();

    //Display only if valid
    if (m_isValidToCreate)
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << m_menuName << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        for (int i = 0; i < m_optionsList.size(); ++i)
        {
            std::cout << i+1 << ". " << m_optionsList[i] << std::endl;
        }

        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> m_choice;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
    }
}

int SDBMS::Menu::GetChoice()
{
    return m_choice;
}
