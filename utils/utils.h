#pragma once
class utils
{
public:
	static void runBat(const char*, bool bwait, bool showWindow);
};
/*
 *基本类型的char数组表示
 */
template <class T>
union TypeUnion {
	T s;
	char sBuff[sizeof(T)];
};