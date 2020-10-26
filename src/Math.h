#pragma once

struct Vec2
{
	float x, y;

	Vec2()
		: x(0.0f), y(0.0f)
	{}

	Vec2(float x, float y)
		: x(x), y(y)
	{}
};

struct Vec3
{
	float x, y, z;

	Vec3()
		: x(0.0f), y(0.0f), z(0.0f)
	{}

	Vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}
};

struct Vec4
{
	float x, y, z, w;

	Vec4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	Vec4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}
};

Vec2 VecToNdc(Vec2 vec, int width, int height);