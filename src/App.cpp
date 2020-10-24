#include "App.h"

void App::MainLoop()
{
	auto delta = clock.Mark() * 0.69f;

	console.SetTitle(clock.Time());

	if (wnd.keyboard.IsPressed({ VK_F1 }) && !wnd.gfx().gui.IsEnabled())
		wnd.gfx().gui.Toggle();
	if (wnd.keyboard.IsPressed({ VK_F2 }) && wnd.gfx().gui.IsEnabled())
		wnd.gfx().gui.Toggle();


	wnd.gfx().StartFrame(0.075f, 0.067f, 0.094f);

	for (auto& cube : cubes)
	{
		cube->Update(delta);
		cube->Draw(wnd.gfx());
	}

	/// [TODO]: for (auto& gui : guis) gui->Render();
	if (wnd.gfx().gui.IsEnabled())
	{
		wnd.gfx().camera.Gui();
		Gui();
	}

	wnd.gfx().EndFrame();
}