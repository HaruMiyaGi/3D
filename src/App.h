#pragma once
#include "Window.h"
#include "Console.h"
#include "Clock.h"
#include "Random.h"

#include "Shape.h"
#include "Line.h"

#include "Math.h"
#define PI 3.1315f

class App
{
public:
	App()
		: wnd(640, 480, "owo")
	{
		for (auto i = 0; i < 60; i++)
		{
			std::vector<float> rng;
			rng.push_back(random.Number<float>(0.0f, PI * 2.0f));
			rng.push_back(random.Number<float>(0.0f, PI * 2.0f));
			rng.push_back(random.Number<float>(0.0f, PI * 2.0f));
			rng.push_back(random.Number<float>(0.0f, PI * 2.0f));
			rng.push_back(random.Number<float>(0.0f, PI * 2.0f));
			rng.push_back(random.Number<float>(0.0f, PI * 2.0f));
			rng.push_back(random.Number<float>(0.0f, PI * 0.3f));
			rng.push_back(random.Number<float>(0.0f, PI * 0.3f));
			rng.push_back(random.Number<float>(0.0f, PI * 0.3f));
			rng.push_back(random.Number<float>(6.0f, 20.0f));

			cubes.push_back(std::make_unique<Shape>(wnd.gfx(), rng));
		}


		for (auto i = 0; i < 1; i++)
			lines.push_back(std::make_unique<Line>(wnd.gfx()));

	}
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
	Random random;
	Window wnd;
	std::vector<std::unique_ptr<class Line>> lines;
	std::vector<std::unique_ptr<class Shape>> cubes;
};