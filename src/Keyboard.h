#pragma once
#include <bitset>
#include <vector>

class Keyboard
{
	friend class Window;
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator = (const Keyboard&) = delete;
public:
	bool IsPressed(std::vector<unsigned char> keys) const
	{
		for (auto key : keys)
			if (!IsDown(key))
				return false;
		return true;
	}
	void EnableAutoRepeat()
	{
		auto_repeat = true;
	}
	void DisableAutoRepeat()
	{
		auto_repeat = false;
	}
	bool IsAutoRepeatEnabled()
	{
		return auto_repeat;
	}
private:
	bool IsDown(unsigned char keycode) const
	{
		return keystates[keycode];
	}
private:
	void OnKeyPress(unsigned char keycode)
	{
		keystates[keycode] = true;
	}
	void OnKeyRelease(unsigned char keycode)
	{
		keystates[keycode] = false;
	}
	void ClearStates()
	{
		keystates.reset();
	}
private:
	bool auto_repeat = false;
	std::bitset<256> keystates;
};