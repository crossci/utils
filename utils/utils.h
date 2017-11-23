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
};
/*
 *�������͵�char�����ʾ
 */
template <class T>
union TypeUnion {
	T s;
	char sBuff[sizeof(T)];
};