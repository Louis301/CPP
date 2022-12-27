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
#include <map>

#include <windows.h>
#include <conio.h>

using namespace std;

map<wchar_t, int> Alfabeth_Forward;
map<int, wchar_t> Alfabeth_Backward;

//-----------------------------------------------------------------------------------------------------
void Init_Alfabeth()
{
	const wstring alfabeth = L" ,.?!:;^&*/+-=`~\"\'<>()%$№@#[]{}|\\\n\t_абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < alfabeth.size(); i++)
	{
		Alfabeth_Forward[alfabeth[i]] = i + 1;
		Alfabeth_Backward[i + 1] = alfabeth[i];
	}
}

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

	wcout << L"Файл "<< path << L" считан\n";
	infile.close();
}

//-----------------------------------------------------------------------------------------------------
void Gamma_Generation(const wstring &content, wstring &gamma)
{
	int i;
	gamma = L"";

	for (i = 0; i < content.size(); i++)
		gamma += Alfabeth_Backward[rand() % Alfabeth_Forward.size() + 1];
}

//-----------------------------------------------------------------------------------------------------
void Encrypt_File(const wstring &path)
{
	// 1. Считываем исходный файл
	wstring text;
	Get_File(path, text);

	// 2. Генерация гаммы
	wstring gamma;
	Gamma_Generation(text, gamma);
	Set_File(L"gamma_" + path, gamma);

	// 3. Шифрование
	int i;
	int encrypted_num;
	wstring crypt_msg = L"";

	for (i = 0; i < text.size(); i++)
	{
		encrypted_num = Alfabeth_Forward[text[i]] + Alfabeth_Forward[gamma[i]];

		if (encrypted_num <= Alfabeth_Forward.size())
			crypt_msg += Alfabeth_Backward[encrypted_num];
		else
			crypt_msg += Alfabeth_Backward[(encrypted_num % Alfabeth_Forward.size())];
	}

	Set_File(path, crypt_msg);
}

//-----------------------------------------------------------------------------------------------------
void Decrypt_File(wstring &path)
{
	// 1. Получаем зашифрованный текст
	wstring crypt_msg;
	Get_File(path, crypt_msg);

	// 2. Получаем гамму
	wstring gamma;
	Get_File(L"gamma_" + path, gamma);

	// 3. Расшифровываем текст
	int i;
	wstring decrypt_msg = L"";

	for (i = 0; i < crypt_msg.size() - 1; i++)
	{
		int simbol_id;

		if (Alfabeth_Forward[gamma[i]] < Alfabeth_Forward[crypt_msg[i]])
		{
			simbol_id = Alfabeth_Forward[crypt_msg[i]] - Alfabeth_Forward[gamma[i]];
		}
		else
		{
			simbol_id = (Alfabeth_Forward.size() + Alfabeth_Forward[crypt_msg[i]]) - Alfabeth_Forward[gamma[i]];
		}

		decrypt_msg += Alfabeth_Backward[simbol_id];
	}

	Set_File(path, decrypt_msg);
}

//-----------------------------------------------------------------------------------------------------
int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	SetConsoleCP(1251);

	Init_Alfabeth();

	int mode;
	wstring path;

	wcout << L"Путь до исходного файла: ";
	getline(wcin, path);

	wcout << path << endl;

	wifstream fin(path);
		
	if (fin.is_open())
	{
		wcout << endl;
		wcout << L"Выберите режим работы:\n";
		wcout << L"- шифрование (1)\n";
		wcout << L"- дешифрование (2)\n";
		wcout << L"\nВыбор -> ";
		wcin >> mode;
		wcout << endl;

		switch (mode)
		{
		case 1:
			// 1. Шифрование файла
			Encrypt_File(path);
			break;

		case 2:
			// 2. Дешифрование файла
			Decrypt_File(path);
			break;
		}
	}
	else
	{
		wcout << L"\nFile not exists";
	}

	fin.close();
	

	_getch();
	return 0;
}