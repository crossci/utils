#include <iostream>
#include "Utils.h"
using namespace std;

int main(int argc, char* argv[])
{
	const char* fileName = "test.txt";
	char path[_MAX_PATH];
	memset(path, 0, sizeof(path));
	Utils::generateFullPath(fileName, path);
	cout << path << endl;
	system("pause");
}