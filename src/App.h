#pragma once
#include "Window.h"
#include "Console.h"
#include "Clock.h"

#include "Shape.h"
#include "Shape2.h"

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
	void Gui()
	{
		if (ImGui::Begin("[F1]", 0, ImGuiWindowFlags_NoResize))
		{
			ImGui::Text("Hey :3");
		}
		ImGui::End();
	}
private:
	Clock clock;
	Console console;
	Window wnd;

	Shape shape = Shape(wnd.gfx());
	Shape2 shape2 = Shape2(wnd.gfx());
	Shape2 shape3 = Shape2(wnd.gfx());
};