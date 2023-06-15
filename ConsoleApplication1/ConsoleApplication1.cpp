#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>


enum EKey
{
    EK_1 = 49,
    EK_2 = 50,
    EK_3 = 51,
    EK_Home = 71,
    EK_Esc = 27,
};

enum EScreen
{
    ES_Main,
    ES_Create_Project,
    ES_Show_Projects,
    ES_Add_Task
};

struct ATask
{
    std::string* Title;
    std::string* Discription;
    std::string* State;
};

struct AProject
{
    std::string* Title;
    std::string* Discription;
    std::string* Start_Date;
    std::string* End_Date;
    std::vector<ATask*> Tasks;
};


int Projects_List_Size = 0;
bool Exit_Program = false;

EScreen Screen_Id = ES_Main;
AProject** Projects_List = new AProject*[Projects_List_Size];
AProject* Selected_Project;


//------------------------------------------------------------------------------------------
void Add_Project(const AProject *new_project)
{
    Projects_List_Size++;

    int i;
    AProject** temp_projects_list = new AProject*[Projects_List_Size];

    for (i = 0; i < Projects_List_Size; ++i)
    {
        if (i == 0)
            temp_projects_list[i] = (AProject *)new_project;
        else
            temp_projects_list[i] = Projects_List[i - 1];
    }

    delete[] Projects_List;
    Projects_List = temp_projects_list;
}

//// ------------------------------------------------------------------------------------------
//void Delete_Item(int item_id)
//{
//    Menu_List_Size--;
//
//    if (Current_Item_ID == Menu_List_Size)
//        Current_Item_ID--;
//
//    int i;
//    string* temp_menu_list = new string[Menu_List_Size];
//
//    for (i = 0; i < Menu_List_Size; ++i)
//    {
//        if (i >= item_id)
//            temp_menu_list[i] = Menu_List[i + 1];
//        else
//            temp_menu_list[i] = Menu_List[i];
//    }
//
//    delete[] Menu_List;
//    Menu_List = temp_menu_list;
//}

void Show_Projects_Screen()
{
    std::cout << "ВАШИ ПРОЕКТЫ\n\n";

    if (Projects_List_Size > 0)
    {
        for (int i = 0; i < Projects_List_Size; ++i)
        {
            std::cout << i + 1 << ". " << *Projects_List[i]->Title << std::endl;
            if (Projects_List[i]->Tasks.size() > 0)
            {
                for (auto task : Projects_List[i]->Tasks)
                    std::cout << "- " << *task->Title << std::endl;
                printf("\n");
            }
            else
            {
                printf("- Нет задач\n");
            }
        }
    }
    else
    {
        printf("Нет проектов\n");
    }


    std::cout << std::endl;

    std::cout << "  1. Добавить проект\n";
    std::cout << "  2. Управление проектом\n";
    std::cout << "  HOME. Вернуться на главный экран\n";
    std::cout << "\nВыбор > ";

    while (true)
    {
        switch (_getch())
        {
        case EK_1:
            system("cls");
            Screen_Id = ES_Create_Project;
            return;

        case EK_2:
            printf("\n\n");
            printf("Введите номер проекта: ");
            // Screen_Id = ES_Project_Control;
            return;

        case EK_Home:
            system("cls");
            Screen_Id = ES_Main;
            return;

        default:
            break;
        }
    }
}

//------------------------------------------------------------------------------------------
void Main_Screen()
{
    std::cout << "Добро пожаловать в Систему контроля проектов \"СКП\"!\n\n";

    std::cout << "  1. Создать проект\n";
    std::cout << "  2. Отобразить существующие проекты\n";
    std::cout << "  ESC. Выйти\n";
    std::cout << "\nВыбор > ";

    while (true)
    {
        switch (_getch())
        {
        case EK_1:
            system("cls");
            Screen_Id = ES_Create_Project;
            return;

        case EK_2:
            system("cls");
            Screen_Id = ES_Show_Projects;
            return;

        case EK_Esc:
            std::cout << "\nВы покидаете систему";
            Exit_Program = true;
            return;

        default:
            break;
        }
    }
}

//------------------------------------------------------------------------------------------
void Create_Project_Screen()
{
    std::cout << "СОЗДАНИЕ ПРОЕКТА\n\n";

    std::string* title = new std::string();
    std::string* discription = new std::string();
    std::string* start_date = new std::string();
    std::string* end_date = new std::string();

    std::cout << "Название: ";      std::getline(std::cin, *title);
    std::cout << "Описание: ";      std::getline(std::cin, *discription);
    std::cout << "Дата начала: ";   std::getline(std::cin, *start_date);
    std::cout << "Крайний срок: ";  std::getline(std::cin, *end_date);

    Add_Project(new AProject{ title , discription , start_date , end_date });


    std::cout << std::endl;

    std::cout << "  1. Перейти к постановке задач для проекта\n";
    std::cout << "  2. Показать все проекты\n";
    std::cout << "  3. Создать проект\n";
    std::cout << "  HOME. Вернуться на главный экран\n";

    std::cout << "\nВыбор > ";

    while (true)
    {
        switch (_getch())
        {
        case EK_1:
            Screen_Id = ES_Add_Task;
            Selected_Project = Projects_List[0];
            return;

        case EK_2:
            system("cls");
            Screen_Id = ES_Show_Projects;
            return;

        case EK_3:
            system("cls");
            Screen_Id = ES_Create_Project;
            return;

        case EK_Home:
            system("cls");
            Screen_Id = ES_Main;
            return;

        default:
            break;
        }
    }
}

//------------------------------------------------------------------------------------------
void Add_Task_Screen()
{
    std::cout << "НОВАЯ ЗАДАЧА\n\n";
    
    std::string* title = new std::string();
    std::string* discription = new std::string();
    std::string* state = new std::string();

    std::cout << "Название: ";      std::getline(std::cin, *title);
    std::cout << "Формулировка: ";  std::getline(std::cin, *discription);
    std::cout << "Состояние: ";     std::getline(std::cin, *state);

    Selected_Project->Tasks.push_back(new ATask{ title , discription , state });
    

    std::cout << std::endl;

    std::cout << "  1. Добавить ещё одну задачу\n";
    std::cout << "  HOME. Вернуться на главный экран\n";

    std::cout << "\nВыбор > ";

    while (true)
    {
        switch (_getch())
        {
        case EK_1:
            Screen_Id = ES_Add_Task;
            return;

        case EK_Home:
            system("cls");
            Screen_Id = ES_Main;
            return;

        default:
            break;
        }
    }
}

//------------------------------------------------------------------------------------------
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (!Exit_Program)
    {
        switch (Screen_Id)
        {
        case ES_Main:
            Main_Screen();
            break;

        case ES_Create_Project:
            Create_Project_Screen();
            break;

        case ES_Show_Projects:
            Show_Projects_Screen();
            break;

        case ES_Add_Task:
            Add_Task_Screen();
            break;

        default:
            break;
        }
    }

    return 0;
}
