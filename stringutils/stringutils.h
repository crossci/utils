#include <string>
#include <vector>
#include "..\base\define.h"

class DLL_SAMPLE_API stringutils
{
public:
	static void converToUpper(std::string& src);

	static void converToLower(std::string& src);

	static std::string ws2s(const std::wstring& ws);

	static std::wstring s2ws(const std::string& s);

	static std::string utf82gbk(const char* utf);

	static std::string gbk2utf8(const char* gbk);

	static std::vector<std::string> split(std::string str, std::string pattern);

	static std::string number2string(long long value);

	bool isChineseCharacter(std::string str);
};