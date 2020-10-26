#include "Math.h"

Vec2 VecToNdc(Vec2 vec, int width, int height)
{
	Vec2 res;
	res.x = vec.x / width * 2.0f - 1.0f;
	res.y = 1.0f - vec.y / height * 2.0f;

	return res;
}