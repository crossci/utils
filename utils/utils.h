#pragma once
class utils
{
public:
	static void runBat(const char*, bool bwait, bool showWindow);
};
/*
 *�������͵�char�����ʾ
 */
template <class T>
union TypeUnion {
	T s;
	char sBuff[sizeof(T)];
};