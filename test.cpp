#include <iostream>
#include "Utils.h"
#include <io.h>
using namespace std;

int main(int argc, char* argv[])
{
	const char* fileName = "C:\\Users\\zhukunkun\\Desktop\\test\\1\\2.txt";
	FILE* file = Utils::openFile(fileName,"w");
	fclose(file);
	system("pause");
}