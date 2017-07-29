#include "stringutils.h"
#include <algorithm>
void stringutils::converToUpper(std::string& src)
{
	transform(src.begin(), src.end(), src.begin(), toupper);
}

void stringutils::converToLower(std::string& src)
{
	transform(src.begin(), src.end(), src.begin(), tolower);
}

