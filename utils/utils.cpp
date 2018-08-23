#include "utils.h"
#include <winsock2.h>
#include <Windows.h>
#include <time.h>
#pragma comment(lib,"ws2_32")

__int64 CompareFileTime2(FILETIME time1, FILETIME time2)
{
	__int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
	__int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;


	return   b - a;
}

void utils::runBat(const char* cmd,bool bwait,bool showWindow)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD createFlag = CREATE_NO_WINDOW;
	if (showWindow)
	{
		createFlag = CREATE_NEW_CONSOLE;
	}
	if (CreateProcessA(NULL,
		(LPSTR)cmd,
		NULL,
		NULL,
		FALSE,
		createFlag,
		NULL,
		NULL,
		&si, &pi))
	{
		if (bwait)
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

//CPU利用率  
FILETIME m_preidleTime;
FILETIME m_prekernelTime;
FILETIME m_preuserTime;

int utils::get_cpu_useage()
{
	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);


	int idle = CompareFileTime2(m_preidleTime, idleTime);
	int kernel = CompareFileTime2(m_prekernelTime, kernelTime);
	int user = CompareFileTime2(m_preuserTime, userTime);


	if (kernel + user == 0)
		return 0.0;
	//（总的时间-空闲时间）/总的时间=占用cpu的时间就是使用率  
	double cpu = abs((kernel + user - idle) * 100 / (kernel + user));

	m_preidleTime = idleTime;
	m_prekernelTime = kernelTime;
	m_preuserTime = userTime;
	return cpu;
}

int utils::get_memory_useage()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return statex.dwMemoryLoad;
}



bool utils::get_ip(std::vector<std::string>& ips)
{
	//1.初始化wsa  
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		return false;
	}
	//2.获取主机名  
	char hostname[256];
	ret = gethostname(hostname, sizeof(hostname));
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	//3.获取主机ip  
	HOSTENT* host = gethostbyname(hostname);
	if (host == NULL)
	{
		return false;
	}
	//4.逐个转化为char*并拷贝返回  
	int ip_count = host->h_length;
	for (int i = 0; i < ip_count; i++)
	{
		in_addr* addr = (in_addr*)*host->h_addr_list;
		ips.push_back(inet_ntoa(addr[i]));
	}
	return true;
}

unsigned __int64 utils::get_uid()
{
	ULONGLONG t = GetTickCount64();
	static unsigned __int64 i = 0;
	InterlockedIncrement(&i);
	unsigned __int64 ret = t << 32 | i;
	return ret;
}