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

	float Mark()
	{
		const auto old_time = time;
		time = std::chrono::steady_clock::now();
		const std::chrono::duration<float> frameTime = time - old_time;
		return frameTime.count();
	}

private:
	std::chrono::steady_clock::time_point time;
};