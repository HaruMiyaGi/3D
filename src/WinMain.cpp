#include "App.h"

Window::WndClass Window::WndClass::wnd_class; // WindowClass instance (needed for window creation)

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	return App{}.Go();
}