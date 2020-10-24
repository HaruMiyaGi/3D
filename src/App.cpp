#include "App.h"

void App::MainLoop()
{
	console.SetTitle(clock.Peek());

	if (wnd.keyboard.IsPressed({ VK_F1 }))
		wnd.gfx().gui.Toggle();


	wnd.gfx().StartFrame(0.075f, 0.067f, 0.094f);

	shape.Update(clock.Peek(), false);
	shape.Draw(wnd.gfx());

	shape2.Update(clock.Peek(), true);
	shape2.Draw(wnd.gfx());

	shape3.Update(clock.Peek(), true);
	shape3.Draw(wnd.gfx());

	if (wnd.gfx().gui.IsEnabled())
	{
		wnd.gfx().camera.Gui();
		Gui();
		shape.Gui();
	}

	wnd.gfx().EndFrame();
}