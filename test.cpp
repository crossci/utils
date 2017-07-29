#include <iostream>
#include "fileutils\FileUtils.h"
#include <io.h>
#include <Windows.h>
#include "md5\MD5Utils.h"
#include <algorithm>
using namespace std;
#ifdef _DEBUG

int main(int argc, char* argv[])
{
	//const char* fileName = "C:\\Users\\zhukunkun\\Desktop\\test\\1\\2.txt";
	//FILE* file = FileUtils::openFile(fileName, "w");
	//fclose(file);

	//智能指针（智能操作堆上的对象）
	//CPtrHelper<char> fieddle1 = new char[10];
	//memset(fieddle1, 0, 10);
	//memcpy(fieddle1, "test", strlen("test"));
	//CPtrHelper<char> fieddle2(fieddle1);

	////读写文件
	//int fileLen = 0;
	//CPtrHelper<char> fileContent = FileUtils::getTXTFile("E:\\test_space\\ConsoleApplication1\\Utils\\todolist.txt", fileLen);
	//if (fileContent)
	//{
	//	cout << fileContent << endl;
	//}
	//
	//if (FileUtils::writeToFile("3.log", fileContent, fileLen, "w"))
	//{
	//	cout << "write success!" << endl;
	//}
	string md5str = MD5Utils::getFileMD5("E:\\test_space\\ConsoleApplication1\\Utils\\test.cpp");
	cout << md5str<< endl;
	transform(md5str.begin(), md5str.end(), md5str.begin(), toupper);
	cout << md5str << endl;
	system("pause");
}

#else
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif