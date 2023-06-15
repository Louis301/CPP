
#include "Engine.h"

#include <iostream>
#include <windows.h>


enum EColor
{
	EC_Black,
	EC_Dark_Blue,
	EC_Dark_Green,
	EC_Light_Blue,
	EC_Red,
	EC_Dark_Purple,
	EC_Dark_Yellow,
	EC_Grey,
	EC_Dark_Grey,
	EC_Blue,
	EC_Green,
	EC_Biruza,
	EC_Pink,
	EC_Purple,
	EC_Yellow,
	EC_White
};

struct ASymbol
{
	EColor Text_Color, Bg_Color;
	char Character;
};



const int Console_Width = 170 + 1;  // 170
const int Console_Height = 40;  // 40

ASymbol Console_Matrix[Console_Height][Console_Width];



//----------------------------------------------------------------------------------------------------
void Set_Console_Color(EColor text_color, EColor bg_color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg_color << 4) | text_color));
}


//----------------------------------------------------------------------------------------------------
//
//	Запись сообщения в матрицу консоли
//
void Init_Msg(int offset_x, int offset_y, std::string msg, EColor text_color, EColor bg_color)
{
	int i, j;

	if (offset_x >= 0 && (offset_x + msg.size()) < Console_Width &&
		offset_y >= 0 && offset_y < Console_Height)
	{
		for (j = 0; j < msg.size(); ++j)
			Console_Matrix[offset_y][j + offset_x] = ASymbol{ text_color, bg_color, msg[j] };
	}
}


//----------------------------------------------------------------------------------------------------
void Init_Console()
{
	int i, j;

	for (i = 0; i < Console_Height; ++i)
		for (j = 0; j < Console_Width; ++j)
			Console_Matrix[i][j] = (j == Console_Width - 1) ? ASymbol{ EC_White, EC_Black, '\n' } : ASymbol{ EC_White, EC_Black, '$' };


	Init_Msg(1, 1, "Hello, World!", EC_Red, EC_Black);
	Init_Msg(3, 2, "Hello, World!", EC_Red, EC_Black);
	Init_Msg(5, 3, "Hello, World!", EC_Red, EC_Black);
}


//----------------------------------------------------------------------------------------------------
//
//	Печать матрицы консоли
//
void Print_Console()
{
	int i, j;

	for (i = 0; i < Console_Height; ++i)
	{
		for (j = 0; j < Console_Width; ++j)
		{
			Set_Console_Color(Console_Matrix[i][j].Text_Color, Console_Matrix[i][j].Bg_Color);
			std::cout << Console_Matrix[i][j].Character;
		}
	}
}