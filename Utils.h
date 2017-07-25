
#pragma once
#include <vector>
class Utils
{
public:
	static bool splitFileName(const char* fileName, char* name, char* ext);

	static void getTimeArray(std::vector<int>& vector);

	static void GetCurrentDir(char* curDir);

	static void generateFullPath(const char* fileName,char* pathName);
};