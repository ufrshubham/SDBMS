#include "Menu.h"
#include <iostream>


void Menu::CheckValidity()
{
    if (!m_optionsList.empty() && (m_menuName.size() != 0))
    {
        m_isValidToCreate = true;

    }
}

Menu::Menu()
{
    m_isValidToCreate = false;
    m_choice = 0;
}


Menu::~Menu()
{
}

std::string Menu::GetOptionsList()
{
    return std::string();
}

void Menu::SetOptionsList(const std::vector<std::string> optionsList)
{
    m_optionsList = optionsList;
}

std::string Menu::GetMenuName()
{
    return m_menuName;
}

void Menu::SetMenuName(const std::string menuName)
{
    m_menuName = menuName;
}

void Menu::DisplayMenu()
{
    CheckValidity();

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

int Menu::GetChoice()
{
    return m_choice;
}
