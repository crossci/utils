#pragma once




class utils
{
public:
	static void runBat(const char*, bool bwait, bool showWindow);
	static int get_cpu_useage();
	static int get_memory_useage();
	static bool get_ip(char* ip);
};
/*
 *基本类型的char数组表示
 */
template <class T>
union TypeUnion {
	T s;
	char sBuff[sizeof(T)];
};