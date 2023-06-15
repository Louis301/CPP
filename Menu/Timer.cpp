#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;


enum EKeys
{
	EK_W = 119,
	EK_S = 115,
	EK_A = 97,
	EK_D = 100,
	EK_ESC = 27,
	EK_UP = 72,
	EK_DOWN = 80,
	EK_LEFT = 75,
	EK_RIGHT = 77,
	EK_ENTER = 13,
	EK_SPACE = 32,
	EK_Y = 121,
	EK_N = 110
};


int Menu_List_Size;
int Current_Item_ID;
bool Exit_Program = false;
string* Menu_List;
string Menu_Title;


// ------------------------------------------------------------------------------------------
void Add_Item(string new_item)
{
	Menu_List_Size++;

	int i;
	string* temp_menu_list = new string[Menu_List_Size];

	for (i = 0; i < Menu_List_Size; ++i)
	{
		if (i == 0)
			temp_menu_list[i] = new_item;
		else
			temp_menu_list[i] = Menu_List[i - 1];
	}

	delete[] Menu_List;
	Menu_List = temp_menu_list;
}

// ------------------------------------------------------------------------------------------
void Delete_Item(int item_id)
{
	Menu_List_Size--;

	if (Current_Item_ID == Menu_List_Size)
		Current_Item_ID--;

	int i;
	string* temp_menu_list = new string[Menu_List_Size];

	for (i = 0; i < Menu_List_Size; ++i)
	{
		if (i >= item_id)
			temp_menu_list[i] = Menu_List[i + 1];
		else
			temp_menu_list[i] = Menu_List[i];
	}

	delete[] Menu_List;
	Menu_List = temp_menu_list;
}

// ------------------------------------------------------------------------------------------
void Init_Menu()
{
	Menu_Title = "MENU";
	Menu_List_Size = 0;
	Current_Item_ID = 0;
	Menu_List = new string[Menu_List_Size];
}

// ------------------------------------------------------------------------------------------
void Print_Menu()
{
	if (Menu_List_Size == 0)
	{
		cout << "- Empty -" << endl;
	}
	else
	{
		int i, j;
		int item_indent;
		string item;

		for (i = 0; i < Menu_List_Size; ++i)
		{
			if (i == Current_Item_ID)
			{
				item = " < " + Menu_List[i] + " > ";
			}
			else
			{
				item = Menu_List[i];
			}

			cout << item << endl;
		}
	}
	cout << endl;
}

void Menu_Control()
{
	if (Menu_List_Size == 0)
	{
		switch (_getch())
		{
		case EK_ESC:
			Exit_Program = true;
			break;

		default:
			break;
		}
	}
	else
	{
		switch (_getch())
		{
		case EK_UP:
			if (Current_Item_ID > 0)
				Current_Item_ID--;
			break;

		case EK_DOWN:
			if (Current_Item_ID < Menu_List_Size - 1)
				Current_Item_ID++;
			break;

		case EK_ENTER:
			Delete_Item(Current_Item_ID);
			break;

		case EK_SPACE:
			Add_Item("new_item");
			break;

		case EK_ESC:
			Exit_Program = true;
			break;

		default:
			break;
		}
	}
}

// ------------------------------------------------------------------------------------------
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Init_Menu();
	
	Add_Item("111111");
	Add_Item("222");
	Add_Item("33332");
	Add_Item("44");
	Add_Item("5555");

	// system("\"Tic Tac Toe.exe\"");  - запуск подпрограммы

	while (!Exit_Program)
	{
		Print_Menu();
		Menu_Control();
		system("cls");
	}


	return 0;
}