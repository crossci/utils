#include "Utils.h"
#include <Windows.h>
#include <time.h>

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

void Utils::getTimeArray(std::vector<int>& vector)
{
	vector.clear();
	time_t t = time(NULL);
	struct tm* stime = localtime(&t);
	vector.push_back(1900 + stime->tm_year);
	vector.push_back(1 + stime->tm_mon);
	vector.push_back(stime->tm_mday);
	vector.push_back(stime->tm_hour);
	vector.push_back(stime->tm_min);
	vector.push_back(stime->tm_sec);
}

void Utils::GetCurrentDir(char* curDir)
{
	GetCurrentDirectoryA(MAX_PATH, curDir);
}

void Utils::generateFullPath(const char* fileName, char* pathName)
{
	char curDir[MAX_PATH];
	char name[MAX_PATH];
	char ext[MAX_PATH];
	memset(curDir,0,sizeof(curDir));
	memset(name, 0, sizeof(name));
	memset(ext, 0, sizeof(ext));
	splitFileName(fileName, name, ext);
	GetCurrentDir(curDir);
	time_t t = time(NULL);
	struct tm* stime = localtime(&t);
	sprintf(pathName, "%s\\%s_%04d_%02d_%02d_%02d_%02d_%02d.%s", curDir, name,
		1900 + stime->tm_year, 1 + stime->tm_mon,
		stime->tm_mday, stime->tm_hour,
		stime->tm_min, stime->tm_sec, ext);
}