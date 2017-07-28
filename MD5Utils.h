#pragma once
#include "define.h"
#include "PtrHelper.h"

class DLL_SAMPLE_API MD5Utils
{
public:
	static char* getFileMD5(const char* filePath);
};