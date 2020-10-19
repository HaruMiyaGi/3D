#include "App.h"

void App::MainLoop()
{
	console.SetTitle(clock.Peek());

	if (wnd.keyboard.IsPressed({ VK_F1 }))
		wnd.gfx().gui.Toggle();

	wnd.gfx().StartFrame(0.075f, 0.067f, 0.094f);
	wnd.gfx().Shape();
	wnd.gfx().EndFrame();
}