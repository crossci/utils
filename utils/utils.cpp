#include "utils.h"
#include <Windows.h>
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

