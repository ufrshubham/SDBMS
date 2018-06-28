#pragma once

namespace SDBMS
{
    enum MainMenuOptions
    {
        Add_Class_Data = 1,
        Show_Class_Data,
        Edit_Class_Data,
        Delete_Class_Data,
        Save,
        Save_Exit,
        Exit_No_Save,
        MainMenu_Invalid_Choice
    };

    enum EditMenuOptions
    {
        Add_Student_Data = 1,
        Edit_Student_Data,
        Delete_Student_Data,
        Exit,
        Edit_Invalid_Choice
    };

    enum EditStudentDataOptions
    {
        Edit_Name = 1,
        Edit_Eng,
        Edit_Phy,
        Edit_Chem,
        Edit_Math,
        Edit_CompSci,
        Edit_Student_Data_Invalid
    };
}
