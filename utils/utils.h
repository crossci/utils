#pragma once
#include <vector>

typedef struct tagIPInfo
{
	char ip[30];
}IPInfo;

class utils
{
public:
	static void runBat(const char*, bool bwait, bool showWindow);
	static int get_cpu_useage();
	static int get_memory_useage();
	static bool get_ip(std::vector<std::string>& ips);
	static unsigned __int64 get_uid();
};
/*
 *基本类型的char数组表示
 */
template <class T>
union TypeUnion {
	T s;
	char sBuff[sizeof(T)];
};