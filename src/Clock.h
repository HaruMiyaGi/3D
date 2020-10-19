#pragma once
#include <chrono>

class Clock
{
public:
	Clock()
		: time(std::chrono::steady_clock::now())
	{}

	float Peek() const
	{
		return std::chrono::duration<float>(std::chrono::steady_clock::now() - time).count();
	}

private:
	std::chrono::steady_clock::time_point time;
};