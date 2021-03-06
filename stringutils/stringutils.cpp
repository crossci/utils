#include "stringutils.h"
#include <algorithm>
#include <winsock2.h>
#include <Windows.h>
void stringutils::converToUpper(std::string& src)
{
	transform(src.begin(), src.end(), src.begin(), toupper);
}

void stringutils::converToLower(std::string& src)
{
	transform(src.begin(), src.end(), src.begin(), tolower);
}

std::string stringutils::ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);					// curLocale = "C";
	setlocale(LC_ALL, "chs");                                           //中文地区
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = ws.size() + 1;										//比要转换的宽字符个数大1
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);											//初始化缓冲区
	size_t   i;
	wcstombs_s(&i, _Dest, _Dsize, _Source, ws.size());
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());								//设置回原来的locale
	return result;
}

std::wstring stringutils::s2ws(const std::string& s)
{
	std::string curlLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;

	wchar_t* _Dest = new wchar_t[_Dsize];
	size_t i;
	mbstowcs_s(&i, _Dest, _Dsize, _Source, s.size());
	std::wstring result = _Dest;
	delete[] _Dest;
	setlocale(LC_ALL, curlLocale.c_str());
	return result;
}

std::string stringutils::utf82gbk(const char* utf)
{
	int i = MultiByteToWideChar(CP_UTF8, 0, utf, -1, NULL, 0);
	WCHAR   *strUnicode = new   WCHAR[i];
	MultiByteToWideChar(CP_UTF8, 0, utf, -1, strUnicode, i);
	i = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	char   *strGBK = new   char[i];
	WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strGBK, i, NULL, NULL);
	std::string	ret = strGBK;
	delete[] strGBK;
	return ret;
}
std::string stringutils::gbk2utf8(const char* gbk)
{
	int i = MultiByteToWideChar(CP_ACP, 0, gbk, -1, NULL, 0);
	WCHAR   *strGBK = new   WCHAR[i];
	wmemset(strGBK, 0, i);
	MultiByteToWideChar(CP_ACP, 0, gbk, -1, strGBK, i);
	i = WideCharToMultiByte(CP_UTF8, 0, strGBK, -1, NULL, 0, NULL, NULL);
	char   *strUTF8 = new   char[i];
	memset(strUTF8, 0, i);
	WideCharToMultiByte(CP_UTF8, 0, strGBK, -1, strUTF8, i, NULL, NULL);
	std::string	ret = strUTF8;
	delete[] strUTF8;
	return ret;
}

std::vector<std::string> stringutils::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

std::string stringutils::number2string(long long value)
{
	char temp[48] = { 0 };
	_i64toa_s(value, temp, 48, 10);
	return temp;
}
bool stringutils::isChineseCharacter(std::string str)
{
	char c = str.c_str()[0];
	if (c & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}

}