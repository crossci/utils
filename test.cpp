#include <iostream>
#include "FileUtils.h"
#include <io.h>
using namespace std;
//
//int main(int argc, char* argv[])
//{
//	const char* fileName = "C:\\Users\\zhukunkun\\Desktop\\test\\1\\2.txt";
//	FILE* file = FileUtils::openFile(fileName, "w");
//	fclose(file);
//
//	//智能指针（智能操作堆上的对象）
//	CPtrHelper<char> fieddle1 = new char[10];
//	memset(fieddle1, 0, 10);
//	memcpy(fieddle1, "test", strlen("test"));
//	CPtrHelper<char> fieddle2(fieddle1);
//
//	//读写文件
//	int fileLen = 0;
//	CPtrHelper<char> fileContent = FileUtils::getTXTFile("E:\\test_space\\ConsoleApplication1\\Utils\\todolist.txt", fileLen);
//	if (fileContent)
//	{
//		cout << fileContent << endl;
//	}
//	
//	if (FileUtils::writeToFile("3.log", fileContent, fileLen, "w"))
//	{
//		cout << "write success!" << endl;
//	}
//	system("pause");
//}