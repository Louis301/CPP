// example.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <process.h>

DWORD WINAPI MyThread(LPVOID lpParam)
{
    puts("Help me");
    return 0;
}

int _tmain()
{
    DWORD dwThreadId;
    HANDLE hThread = CreateThread(
        NULL,              // default security attributes
        0,                 // use default stack size  
        MyThread,          // thread function 
        NULL,             // argument to thread function 
        0,                 // use default creation flags 
        &dwThreadId);   // returns the thread identifier 
    _getch();


    return 0;
}

 