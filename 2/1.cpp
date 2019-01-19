// 1.cpp : 定义控制台应用程序的入口点。
//

#include "PtrHelper.h"
#include <iostream>
#include <map>
using namespace std;

class A
{
public:
	virtual ~A()
	{
		int a = 0;
	}
	void AddRef()
	{

	}
	void Release()
	{

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
template<class T>
T test(T t)
{
	return t;
}
int main(int argc, char* argv[])
{
	//std::map<int, A> mpa;
	//A a;
	//mpa.insert(make_pair(1, a));
	//mpa.insert(make_pair(1, a));
	cout << test(1) << endl;;

	system("pause");
	return 0;
}

