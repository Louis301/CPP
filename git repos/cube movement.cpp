//движение квадрата 2*2 по матрице 10*10 с помощью стрелок
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int vert = 0, gor = 0;
 
int main()
{
	const int n = 10;
    int a[n][n] = {0}, choice;
 
    //----------------------------------
    for(int i = 0; i < n; i++) {
    	for(int j = 0; j < n; j++) {
    		if(i == vert && j == gor) {
    			a[i][j] = 1;
    			a[i][j + 1] = 1;
    			a[i + 1][j + 1] = 1;
    			a[i + 1][j] = 1;
			}
	    }
	}
	
	//----------------------------------
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
		    if(a[i][j] == 0) cout << "0";
		    if(a[i][j] == 1) cout << "*";
		}
		cout << "\n";
	}
	cout << "\nx: " << gor << "\ny: " << vert << "\n";
	
	//----------------------------------
	choice = getch();
	switch(choice) 
	{
        case 72:if(vert > 0) vert--; break;
        case 80: if(vert+1 < n - 1) vert++; break;
        case 75: if(gor > 0) gor--; break;
        case 77: if(gor+1 < n - 1) gor++; break;
        case 27: return 0; 
	}
	
	//----------------------------------
	system("cls");
	main();
    return 0;
}
