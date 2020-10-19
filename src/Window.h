#include <Windows.h>
#include <optional>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Window
{
	class WndClass
	{
	public:
		static const char* GetName()
		{
			return wnd_class.wnd_class_name;
		}
		static HINSTANCE GetInstance()
		{
			return wnd_class.hinst;
		}
	private:
		WndClass()
		{
			WNDCLASSEX wc = { 0 };
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = WndProcSetup;
			wc.hInstance = GetInstance();
			wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
			wc.lpszClassName = GetName();
			RegisterClassEx(&wc);
		}
		~WndClass()
		{
			UnregisterClass(GetName(), GetInstance());
		}
	private:
		static constexpr const char* wnd_class_name = "class";
		HINSTANCE hinst;
		static WndClass wnd_class;
	};
public:
	Window(int width, int height, const char* title)
		: width(width), height(height)
	{
		RECT rect = { 0, 0, width, height };
		AdjustWindowRectEx(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE, 0);

		hwnd = CreateWindowEx(
			NULL, WndClass::GetName(), title,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
			NULL, NULL, WndClass::GetInstance(), this
		);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		
		pGfx = std::make_unique<Graphics>(hwnd, width, height);
	}
	~Window()
	{
		DestroyWindow(hwnd);
	}
	static std::optional<int> HandleMsg()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) return msg.wParam;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return {};
	}
	Graphics& gfx()
	{
		return *pGfx;
	}
public:
	int GetWidth()
	{
		return width;
	}	
	int GetHeight()
	{
		return height;
	}
private:
	static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE)
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WndProcThunk));
			return pWnd->WndProc(hWnd, msg, wParam, lParam);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->WndProc(hWnd, msg, wParam, lParam);
	}

	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (pGfx->gui.WndProc(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_CLOSE:
		{
			PostQuitMessage(69);
		} break;

		/// Keyboard
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			keyboard.OnKeyPress(wParam);
		} break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			keyboard.OnKeyRelease(wParam);
		} break;
		/// =====
		
		/// Mouse
		case WM_MOUSEMOVE:
		{
			const POINTS point = MAKEPOINTS(lParam);

			if (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height)
			{
				mouse.OnMouseMove(point.x, point.y);
				if (!mouse.IsInWindow())
					mouse.OnMouseEnter();
			}
			else
			{
				mouse.OnMouseLeave();
			}

		} break;
		case WM_LBUTTONDOWN:
		{
			mouse.OnLeftPress();
		} break;
		case WM_LBUTTONUP:
		{
			mouse.OnLeftRelease();
		} break;
		case WM_RBUTTONDOWN:
		{
			mouse.OnRightPress();
		} break;
		case WM_RBUTTONUP:
		{
			mouse.OnRightRelease();
		} break;
		/// =====
		
		case WM_KILLFOCUS:
		{
			keyboard.ClearStates();
			mouse.ClearStates();
		} break;

		default: return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
private:
	HWND hwnd;
	int width;
	int height;
public:
	std::unique_ptr<Graphics> pGfx;
	Keyboard keyboard;
	Mouse mouse;
};