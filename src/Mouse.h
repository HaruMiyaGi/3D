#pragma once
#include <optional>
#include <queue>

class Mouse
{
	friend class Window;
public:
	struct RawDelta { int x, y; };
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator = (const Mouse&) = delete;
public:
	std::optional<RawDelta> ReadRawDelta()
	{
		if (delta_buffer.empty())
			return std::nullopt;

		const RawDelta d = delta_buffer.front();
		delta_buffer.pop();
		return d;
	}
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
	void OnRawDelta(int deltaX, int deltaY)
	{
		delta_buffer.push({ deltaX, deltaY });
		while (delta_buffer.size() > 16)
			delta_buffer.pop();
	}
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
	std::queue<RawDelta> delta_buffer;
};