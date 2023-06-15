
//#include "Main.h"



#include <iostream>
#include <chrono>
#include <thread>


template <typename F>
void SetTimer(F&& f, size_t sec, size_t repeat)
{
	while (repeat--) {
		f();
		std::this_thread::sleep_for(std::chrono::seconds(sec));
	}
}

void foo()
{
	std::cout << "Hello" << "\n";
}


int main()
{
    //Init_Console();
    //Print_Console();


    SetTimer(foo, 4, 10);

    return 0;
}
