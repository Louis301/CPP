//concatenation of files

#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <iterator>

using namespace std;

void delElemVect(vector<string> &items, string elem) {
	
	for(vector<string>::iterator id = items.begin(); id < items.end(); id++)
	{
		if(*id == elem) 
		{
			items.erase(id);
			break;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	
	fstream first;
	fstream second;
	fstream third;
	vector<string> firstFile;
	vector<string> secondFile;
	
	first.open("first.txt", fstream::in);
	second.open("second.txt", fstream::in);
	
	//cout << "-------------First------------\n";
	while(!first.eof()) 
	{
		SetConsoleOutputCP(1251);
		string s;
		getline(first, s);
		firstFile.push_back(s);
	}
	first.close(); 
	
	//cout << "\n-------------Second------------\n";
	while(!second.eof()) 
	{
		SetConsoleOutputCP(1251);
		string s;
		getline(second, s);
		secondFile.push_back(s);
	}
	second.close();
	
	cout << firstFile.size() << endl;
	cout << secondFile.size() << endl;
	
	for(auto& elemOfFirst : firstFile) 
	{
		for(auto& elemOfSecond : secondFile) 
		{
			if(elemOfFirst == elemOfSecond) delElemVect(secondFile, elemOfSecond);
		}
	}
	
	cout << firstFile.size() << endl;
	cout << secondFile.size();
	
	
	third.open("third.txt", fstream::out | fstream::app);
	
	for(auto& elemOfFirst : firstFile) third << elemOfFirst << '\n';
	for(auto& elemOfSecond : secondFile) third << elemOfSecond << '\n';
	third.close();
	
	return 0;
}
