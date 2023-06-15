// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// formato.cpp
// запись форматированного вывода в файл с помощью операции вставки (<<)

// я добавил в программу две строки для работы с локалью, чтобы можно было
// записать в файл русские буквы в кодировке UTF-8

#include <io.h>      // для функции _setmode
#include <fcntl.h>   // для константы _O_U16TEXT
#include <fstream>   // для файлового ввода/вывода
#include <iostream>
#include <string>    // для работы с классом wstring
#include <codecvt>   // для работы с фасетом codecvt_utf8 локали
#include <windows.h>

using namespace std;


//-----------------------------------------------------------------------------------------------------
void Set_File(const wstring &path, const wstring &content)
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	// создаем константу, содержащую локаль с нужным фасетом для
	// преобразования символов при сохранении в файл в кодировке UTF-8
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

	wofstream outfile(path); // создать объект класса wofstream
	outfile.imbue(utf8_locale);               // связываем наш поток с нужной локалью

	outfile << content;

	// wcout << L"Файл " << path << L" записан\n";
	outfile.close();
}

//-----------------------------------------------------------------------------------------------------
void Get_File(const wstring& path, wstring& content)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

	wifstream infile(path); // создать объект класса wifstream
	infile.imbue(utf8_locale); // связываем наш поток с нужной локалью

	if (infile.is_open())
	{
		wstring line;

		while (getline(infile, line))
			content = content + line + L"\n";

		wcout << L"Файл " << path << L" считан\n";
	}
	else
	{
		// wcout << L"File not exist\n";
	}

	infile.close();
}

//-----------------------------------------------------------------------------------------------------
int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

	wstring path = L"Unicode.txt";
	wstring content = L" ░ ▒ ▓";

	// Get_File(path, content);

	wcout << content;

	Set_File(L"UTF.txt", content); 


	return 0;
}