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
			freopen_s(&file, "CONOUT$", "w", stdout);
			freopen_s(&file, "CONIN$", "r", stdin);
			HMENU console_menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			EnableMenuItem(console_menu, SC_CLOSE, MF_GRAYED);
			MoveWindow(GetConsoleWindow(), 0, 0, 800, 400, TRUE);
		}
	}
	~Console()
	{
		FreeConsole();
	}
	void SetTitle(float time)
	{
		char title[32];
		sprintf_s(title, "Console [%.1fs]", time);
		SetConsoleTitle(title);
	}
private:
	FILE* file = nullptr;
};