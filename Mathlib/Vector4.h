#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>

template <typename V4T>
class Vector4
{
public:
	V4T x;
	V4T y;
	V4T z;
	V4T w;

	Vector4() : x(0), y(0), z(0), w(0) {}

	Vector4(V4T X, V4T Y, V4T Z, V4T W) : x(X), y(Y), z(Z), w(W) {}

	Vector4 operator+(Vector4<V4T> v)
	{
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	Vector4 operator-(Vector4<V4T> v)
	{
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vector4 operator*(Vector4<V4T> v)
	{
		return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	V4T Magnitude()
	{
		return (V4T)std::sqrt(x*x + y*y + z*z + w*w);
	}

	V4T Dot(Vector4<V4T> v)
	{
		return (V4T)x * v.x + y * v.y + z * v.z + w * v.w;
	}
};
#endif