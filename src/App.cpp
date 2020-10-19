#include "App.h"

void App::MainLoop()
{
	console.SetTitle(clock.Peek());

	if (wnd.keyboard.IsPressed({ VK_CONTROL, 'F' }))
	{
		std::cout << "[Ctrl + F]";
		Sleep(100);
	}

	if (wnd.mouse.IsLeftPressed())
	{
		std::cout << "x: " << wnd.mouse.GetX() << ", y: " << wnd.mouse.GetY() << "\n";
		Sleep(100);
	}

	if (wnd.mouse.IsRightPressed())
	{
		std::cout << "Right Click!\n";
		Sleep(100);
	}

}