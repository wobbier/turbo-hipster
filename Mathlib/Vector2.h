#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

template <typename V2T>
class Vector2
{
public:
	V2T x;
	V2T y;

	Vector2() : x(nullptr), y(nullptr) {}

	Vector2(V2T X, V2T Y) : x(X), y(Y) {}

	Vector2 operator+(Vector2<V2T> v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(Vector2<V2T> v)
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator*(Vector2<V2T> v)
	{
		return Vector2(x * v.x, y * v.y);
	}

	V2T Normalize()
	{
		return (V2T)std::sqrt(x*x + y*y);
	}

	V2T Dot(Vector2<V2T> v)
	{
		return (V2T)x * v.x + y * v.y + z * v.z;
	}
};
#endif