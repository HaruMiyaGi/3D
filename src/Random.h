#pragma once
#include <random>

class Random
{
public:
	template <typename T>
	T Number(T min, T max)
	{
		std::uniform_real_distribution<T> range(min, max);
		return range(rng);
	}
private:
	std::mt19937 rng = std::mt19937(std::random_device{}());
};