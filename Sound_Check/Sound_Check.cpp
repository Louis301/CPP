// https://habr.com/ru/post/318584/

#pragma comment(lib, "/Work/Sound_Check/Audiere/audiere.lib")

#include <iostream> 
#include <conio.h>
#include <windows.h> 
#include <conio.h>
#include "/Work/Sound_Check/Audiere/audiere.h" 

using namespace std;
using namespace audiere;


int main()
{
	setlocale(0, "Russian");
	cout << "Start program\n" << endl;

	AudioDevicePtr device = OpenDevice();

	if (device)
	{
		OutputStreamPtr sound = OpenSound(device, "/Work/Sound_Check/Music/The Black Angels - Young Men Dead.mp3", true);

		if (sound)
		{
			sound->setPitchShift(1.0f);
			sound->play();
			_getch();
		}
		else
		{
			cout << "Sound not found\n";
		}
	}
	else
	{
		cout << "Device not init\n";
	}

	return 0;
}
