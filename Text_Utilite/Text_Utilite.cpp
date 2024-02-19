#include <io.h>      // для функции _setmode
#include <fcntl.h>   // для константы _O_U16TEXT
#include <fstream>   // для файлового ввода/вывода
#include <iostream>
#include <string>    // для работы с классом wstring
#include <codecvt>   // для работы с фасетом codecvt_utf8 локали
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

//-----------------------------------------------------------------------------------------------------
void Set_File(const wstring& path, const wstring& content)
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	// создаем константу, содержащую локаль с нужным фасетом для
	// преобразования символов при сохранении в файл в кодировке UTF-8
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

	wofstream outfile(path); // создать объект класса wofstream
	outfile.imbue(utf8_locale);               // связываем наш поток с нужной локалью

	outfile << content;

	wcout << L"Файл " << path << L" записан\n";
	outfile.close();
}

//-----------------------------------------------------------------------------------------------------
void Get_File(const wstring& path, wstring& content)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

	content = L"";

	wifstream infile(path); // создать объект класса wifstream
	infile.imbue(utf8_locale); // связываем наш поток с нужной локалью

	if (infile.is_open())
	{
		wstring line;

		while (getline(infile, line))
		{
			content = content + line + L"\n";
		}
	}

	wcout << L"Файл " << path << L" считан\n";
	infile.close();
}

//-----------------------------------------------------------------------------------------------------
void In_Order(wstring& content)
{
	vector<wstring> content_strings;
	wstring content_string = L"";

	for (int i = 0; i < content.size(); i++)
	{
		if (content[i] == '\n')
		{
			content_strings.push_back(content_string);
			content_string = L"";
		}
		else
		{
			content_string += content[i];
		}
	}

	for (int i = 0; i < content_strings.size() - 1; i++)
	{
		int min_length = content_strings[i].size();
		int min_length_j = i;
		bool swap = false;

		wstring temp = L"";

		for (int j = i + 1; j < content_strings.size(); j++)
		{
			if (content_strings[j].size() > min_length)
			{
				min_length = content_strings[j].size();
				min_length_j = j;
				swap = true;
			}
		}

		if (swap)
		{
			temp = content_strings[i];
			content_strings[i] = content_strings[min_length_j];
			content_strings[min_length_j] = temp;
		}
	}

	content = L"";

	for (auto& item : content_strings)
		content = content + item + L'\n';
}

//-----------------------------------------------------------------------------------------------------
int main()
{
	wstring content; 

	Get_File(L"Files/Дела.txt", content);
	In_Order(content);
	Set_File(L"Files/Дела.txt", content);

	return 0;
}
