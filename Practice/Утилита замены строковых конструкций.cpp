//утилита замены старых строковых конструкций в текстах на новые
#include <iostream>
#include <Windows.h>
#include <Conio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//service
void reverce(string &str) {
 	string str_2 = "";
	for(int i = str.size() - 1; i >= 0; i--) str_2 += str[i];	
	str = str_2;
}

void search(string &expr) {
	
	int funcFlag, endFuncConstr;
	
	for(int j = expr.size() - 1; j >= 0; j--)
	{
			string tmp = "";
			
			for(int id = 0; id < 4; id++) 
				tmp += expr[j - id];
			reverce(tmp);
			
			if(tmp == "    ") //заменяемое слово (конструкция) в тексте
			{
				endFuncConstr = j + 1;
				funcFlag = j - tmp.size() + 1; 
				//nameFunc = tmp;
				goto isolationConstr;
			}
	}
	
	return;
	
	//-----------------------------алгоритм замены
	isolationConstr:
	
	string str_Res = "  "; //значение, на которое меняется конструкция
	string firstPart = "";
  	string secondPart = "";
  	
  	for(int i = 0; i < funcFlag; i++) 
	  	firstPart += expr[i];
  	for(int i = endFuncConstr; i < expr.size(); i++) 
	  	secondPart += expr[i];
	expr = firstPart + str_Res + secondPart;
	
	search(expr);
}

int main() {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	vector<string> code_vector;
	ifstream fin;
	
	fin.open("site.txt");
	
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
	
	//-----------------------------поиск
	for(auto& elem : code_vector)
	{
		search(elem);
	}
	
	//-----------------------------output
	for(auto elem : code_vector)
	{
		cout << elem << endl;
	}
	
	//-----------------------------writting
	ofstream fout;
	fout.open("new site2.txt", ofstream::app);
	
	if(!fout.is_open())
	{
		cout << "ERROR\n";
	}
	else
	{
		for(auto str : code_vector)
		{
			fout << str << endl;
		}
	}
	
	fout.close();
	
	getch();
	return 0;
}

