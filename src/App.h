#pragma once
#include "Window.h"
#include "Console.h"
#include "Clock.h"

class App
{
public:
	App()
		: wnd(640, 480, "owo")
	{}
	int Go()
	{
		while (true)
		{
			if (const auto ecode = Window::HandleMsg())
				return *ecode;
			MainLoop();
		}
	}
private:
	void MainLoop();
private:
	Clock clock;
	Console console;
	Window wnd;
};