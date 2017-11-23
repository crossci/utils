#include <iostream>
#include "fileutils\FileUtils.h"
#include "stringutils\stringutils.h"
#include <io.h>
#include <Windows.h>
#include "md5\MD5Utils.h"
#include "utils\utils.h"
#include <algorithm>
#include <unordered_map>
#include <time.h>
#include <map>
#include "minidump\minidump.h"
using namespace std;
#ifdef _DEBUG
struct stu{
	char sex;
	int length;
	char name[10];
};

int getLongLongSize(long long n)
{
	char temp[100] = { 0 };
	_i64toa_s(n, temp, 100, 10);
	return strlen(temp);
}
class A
{
public:
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
	operator bool() const
	{
		int a = 0;
		return false;
	}

	bool operator==(const A& pI)
	{
		int a = 0;
		return true;
	}
};
class B 
{
public:
	A a;
	virtual ~B()
	{
		cout << "~B()" << endl;
	}
	bool operator==(const B& pI)
	{
		if (a == pI.a)
		{
			int a = 0;
		}
		return true;
	}
	void test()
	{
		delete this;
	}
};

union Game_State_Union
{
	int value;
	struct
	{
		int game_state : 16;
		int all_time : 8;
		int left_time : 8;
	};
};
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
	/*string md5str = MD5Utils::getFileMD5("E:\\test_space\\ConsoleApplication1\\Utils\\test.cpp");
	cout << md5str<< endl;
	transform(md5str.begin(), md5str.end(), md5str.begin(), toupper);
	cout << md5str << endl;*/
	/*const char* cmd = "test.bat";
	utils::runBat(cmd, false,false);*/

	/*char* str = "1,3,4,5,6";
	std::vector<string> vs = stringutils::split(str, ",");
	std::vector<string>::iterator it = vs.begin();
	for (; it != vs.end(); it++)
	{
	cout << it->c_str() << endl;
	}*/

	/*TypeUnion<long long> myUnion;
	myUnion.s = 10000;
	cout << myUnion.sBuff << endl;

	cout << MD5Utils::getMD5("123456") << endl;

	long long longlongvalue = 123433255;
	cout << stringutils::number2string(longlongvalue).c_str() << endl;

	stu mystu;
	cout << sizeof(mystu) << endl;


	std::unordered_map<int, int> numbers;
	std::unordered_map<int, int>::iterator it;
	for (int i = 0; i < 10; i++)
	{
	numbers.insert(make_pair(5, i));
	}

	it = numbers.lower_bound(5);
	if ((it == numbers.end()) || (it->first != 5))
	{
	cout << it->first << endl;
	}
	B* a = new B();
	a->~B();*/
	/*string str;
	char* temp = "string str";
	str.append(temp, strlen(temp));
	cout << str.c_str() << endl;*/
	//B a1;
	//B a2;
	//if ((1 == 1) && (a1 == a2))
	//{
	//	cout << "" << endl;
	//}
	//char ip[30] = { 0 };
	//vector<std::string> ips;
	//while (1)
	//{
	//	ips.clear();
	//	cout << utils::get_cpu_useage() << endl;
	//	cout << utils::get_memory_useage() << endl;
	//	utils::get_ip(ips);
	//	int size = ips.size();
	//	for (int i = 0; i < size; i++)
	//	{
	//		cout << ips[i].c_str() << endl;
	//	}
	//	Sleep(1000);
	//}
	/*char curDir[MAX_PATH];
	char batPath[MAX_PATH];
	FileUtils::GetCurrentDir(curDir);
	sprintf(batPath, "%s/%s", curDir, "startserver.bat");
	if (FileUtils::is_exist(batPath))
	{
		utils::runBat(batPath, false, false);
	}
	else
	{
		cout << batPath << " is not exist!" << endl;
		system("pause");
	}*/
//char item[96] = { 0 };
//int first_count = 10;
//int data[10] = { 0 };
//for (int i = 0; i < first_count; i++)
//{
//	data[i] = i+10;
//}
//int write_pos = 0;
//for (int i = 0; i < first_count; i++)
//{
//	write_pos += sprintf_s(item + write_pos, 96 - write_pos, "%d,", data[i]);
//}
//item[write_pos - 1] = 0;
//cout << item << endl;
/*int size = 1024 ;
for (int i = 0; i < 20*1024; i++)
{
	char temp[1024];
	memset(temp, 'a', size);
	FileUtils::writeToFile("temp.txt", temp, size, "a+");
}*/
//srand((unsigned int)time(0));
//while (1)
//{
//
//	int password = (rand() << 16 | rand()) % 900000 + 100000;
//	cout << password << endl;
//}
//map<int, int> m;
//for (int i = 0; i < 10; i++)
//{
//	auto it = m.find(1);
//	if (it != m.end())
//	{
//		m.erase(it);
//	}
//	m.insert(make_pair(1,i));
//	
//}
//while (true)
//{
//	int left_time = time(0);
//	cout << (left_time & 0x7f) << endl;
//	cout << left_time << endl;
//}
SetUnhandledExceptionFilter(ExceptionFilter);
char szapipath[MAX_PATH];//（D:\Documents\Downloads\TEST.exe）
memset(szapipath, 0, MAX_PATH);
GetModuleFileNameA(NULL, szapipath, MAX_PATH);

//获取应用程序名称
char szExe[MAX_PATH] = "";//（TEST.exe）
char *pbuf = NULL;
char* szLine = strtok_s(szapipath,"\\",&pbuf);
while (NULL != szLine)
{
	strcpy_s(szExe, szLine);
	szLine = strtok_s(NULL,"\\",&pbuf);
}

//删除.exe
strncpy_s(szapipath, szExe, strlen(szExe)-4);
cout<<szapipath<<endl;//(TEST)
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