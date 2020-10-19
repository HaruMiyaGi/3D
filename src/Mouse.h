#pragma once

#include <iostream>
class Mouse
{
	friend class Window;
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator = (const Mouse&) = delete;
public:
	int GetX() const
	{
		return x;
	}
	int GetY() const
	{
		return y;
	}
	bool IsLeftPressed()
	{
		return left_down;
	}
	bool IsRightPressed()
	{
		return right_down;
	}
	bool IsInWindow()
	{
		return in_window;
	}
private:
	void OnMouseMove(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}
	void OnLeftPress()
	{
		left_down = true;
	}
	void OnLeftRelease()
	{
		left_down = false;
	}
	void OnRightPress()
	{
		right_down = true;
	}
	void OnRightRelease()
	{
		right_down = false;
	}
	void OnMouseEnter()
	{
		in_window = true;
	}
	void OnMouseLeave()
	{
		in_window = false;
	}
	void ClearStates()
	{
		left_down = false;
		right_down = false;
	}
private:
	int x = 0, y = 0;
	bool in_window = true;
	bool left_down = false;
	bool right_down = false;
};