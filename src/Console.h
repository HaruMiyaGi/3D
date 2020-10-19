#pragma once
#include <Windows.h>
#include <iostream>

class Console
{
public:
	Console()
	{
		if (AllocConsole())
		{
			SetConsoleTitle("Console");
			freopen_s(&file, "CONOUT$", "w", stdout);
			freopen_s(&file, "CONIN$", "r", stdin);
		}
	}
	~Console()
	{
		FreeConsole();
	}
private:
	FILE* file = nullptr;
};