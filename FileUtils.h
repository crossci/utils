
#pragma once
#include <vector>
#include "PtrHelper.h"
class FileUtils
{
public:
	static bool splitFileName(const char* fileName, char* name, char* ext);

	static void getTimeArray(std::vector<int>& vector);

	static void GetCurrentDir(char* curDir);

	static void generateFullPath(const char* fileName,char* pathName);

	static FILE* openFile(const char* fileName, const char* mode);

	static int getFileLen(const char* fileName);

	static CPtrHelper<char*> getFile();

	//todo
	//md5
	//crc
	//一些常用的加密算法
	//http 请求 下载
	//运行bat文件
	//遍历目录
	//网络
	//数据库
	//日志系统
	//智能指针
	//内存池 对象池
	//内存泄露
};