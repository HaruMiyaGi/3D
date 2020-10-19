#include "App.h"

int counter = 0;

void App::MainLoop()
{
	std::cout << counter << std::endl;
	counter++;
}