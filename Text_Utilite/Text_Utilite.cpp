#include <io.h>      // ��� ������� _setmode
#include <fcntl.h>   // ��� ��������� _O_U16TEXT
#include <fstream>   // ��� ��������� �����/������
#include <iostream>
#include <string>    // ��� ������ � ������� wstring
#include <codecvt>   // ��� ������ � ������� codecvt_utf8 ������
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

//-----------------------------------------------------------------------------------------------------
void Set_File(const wstring& path, const wstring& content)
{
	// ������������ ������������ ������ ������ � ������ �������
	_setmode(_fileno(stdout), _O_U16TEXT);

	// ������� ���������, ���������� ������ � ������ ������� ���
	// �������������� �������� ��� ���������� � ���� � ��������� UTF-8
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

	wofstream outfile(path); // ������� ������ ������ wofstream
	outfile.imbue(utf8_locale);               // ��������� ��� ����� � ������ �������

	outfile << content;

	wcout << L"���� " << path << L" �������\n";
	outfile.close();
}

//-----------------------------------------------------------------------------------------------------
void Get_File(const wstring& path, wstring& content)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

	content = L"";

	wifstream infile(path); // ������� ������ ������ wifstream
	infile.imbue(utf8_locale); // ��������� ��� ����� � ������ �������

	if (infile.is_open())
	{
		wstring line;

		while (getline(infile, line))
		{
			content = content + line + L"\n";
		}
	}

	wcout << L"���� " << path << L" ������\n";
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

	Get_File(L"Files/����.txt", content);
	In_Order(content);
	Set_File(L"Files/����.txt", content);

	return 0;
}
