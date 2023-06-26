//garland
#include <iostream>
#include <Windows.h>
#include <Conio.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void pause(void)
{
	for(int i = 0; i < 10000000; i++) {};
}

void SetColor(int text, int bg) 
{ 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

vector<string> checking_for_errors(int num)
{
	vector<string> code_vector;
	
	ifstream fin;
	
	if(num == 1) fin.open("functions_planimetry.cpp");
	if(num == 2) fin.open("bgm_1.cpp");
	if(num == 3) fin.open("garland.cpp");
	if(num == 4) fin.open("Snake.cpp");
	
	if(!fin.is_open())
	{
		cout << "ERROR";
	}
	else
	{
		string s;
		while(!fin.eof())
		{
			getline(fin, s);
			code_vector.push_back(s);
		}
	}
	
	fin.close();
	return code_vector;
}

void output(vector<string> code_vector)
{
	for(int i = 0; i < code_vector.size(); i++)
	    {
		    for(int j = 0; j < code_vector[i].size(); j++)
		    {
			    cout << code_vector[i][j];
		        pause();
		    }
		    cout << "\n";
	    }
}

int main()
{
	vector<string> code_vector;
	code_vector = checking_for_errors(1);
	int color[4] = {10, 12, 3, 14};
	
	for(short i = 1; i < 5; i++)
	{
		SetColor(color[i - 1], 0);
		code_vector = checking_for_errors(i);
		output(code_vector);
		cout << "\n=================================\n";
	}

	SetColor(15, 0);
	getch();
	return 0;
}
