#include "Utils.h"
#include <Windows.h>

bool Utils::splitFileName(const char* fileName, char* name, char* ext)
{
	bool ret = false;
	char temp[MAX_PATH];
	memset(temp, 0, sizeof(temp));
	memcpy(temp, fileName, strlen(fileName));
	char* p = strchr(temp, '.');
	if (p)
	{
		const char* fileExt = p + 1;
		memcpy(ext, fileExt, strlen(fileExt));
		*p = 0;
		memcpy(name, temp, strlen(temp));
		ret = true;
	}
	return ret;
}