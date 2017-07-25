#include <iostream>
#include "Utils.h"
using namespace std;

int main(int argc, char* argv[])
{
	const char* fileName = "test";
	char name[_MAX_PATH];
	char ext[_MAX_PATH];
	memset(name, 0, sizeof(name));
	memset(ext, 0, sizeof(ext));
	bool success = Utils::splitFileName(fileName, name, ext);
	if (success)
	{
		cout << name << " " << ext << endl;
	}
	else
	{
		cout <<"failed!" << endl;
	}
	system("pause");
}