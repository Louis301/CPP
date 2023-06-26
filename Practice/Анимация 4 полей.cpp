#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include <conio.h>

using namespace std;


void setCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void cursorHide() {
	CONSOLE_CURSOR_INFO curs = {0};
   	curs.dwSize = sizeof(curs);
  	curs.bVisible = FALSE;
   	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void setColor(int text, int bg) { 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void setMonitorDimensions(int width, int height) {
	RECT r;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

int main() {
	
	const int SIZE = 7;
	
	setMonitorDimensions((SIZE * 2 + 1) * 13, (SIZE * 2 + 1) * 27);
	cursorHide();
	
	for(int y = 0, y2 = SIZE * 2 - 1; 
		y < SIZE, y2 >= SIZE; 
		y ++, y2 --)
	{
		for(int x = 0, x2 = SIZE * 2 - 1; 
			x < SIZE, x2 >= SIZE; 
			x ++, x2 --)
		{
			setColor(10, 0);
			setCur(x, y);
			cout << "A";
			
			setColor(12, 0);
			setCur(x, y2 + 1);
			cout << "b";
			
			setColor(7, 0);
			setCur(x2 + 1, y);
			cout << "C";
			
			setColor(14, 0);
			setCur(x2 + 1, y2 + 1);
			cout << "d";
			
			this_thread::sleep_for(chrono::milliseconds(100));
		}	
		cout << endl;
	}
	
	setColor(15, 0);
	setCur(SIZE, SIZE);
	cout << '@';
	
	this_thread::sleep_for(chrono::milliseconds(500));
	//setMonitorDimensions(500, 500);
	
	setCur(0, SIZE * 2);
	//getch();
	return 0;
}
