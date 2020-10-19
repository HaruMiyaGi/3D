#include "App.h"

void App::MainLoop()
{
	console.SetTitle(clock.Peek());

	if (wnd.keyboard.IsPressed({ VK_CONTROL, 'F'}))
	{
		std::cout << "[Ctrl + F]";
		Sleep(100);
	}

}