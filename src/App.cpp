#include "App.h"

void App::MainLoop()
{
	console.SetTitle(clock.Peek());

	if (wnd.keyboard.IsPressed({ VK_F1 }))
		wnd.gfx().gui.Toggle();

	wnd.gfx().StartFrame(1.0f, 0.0f, 0.0f);
	wnd.gfx().EndFrame();
}