#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

template <typename V3T>
class Vector3
{
public:
	V3T x;
	V3T y;
	V3T z;

	Vector3() : x(0), y(0), z(0) {}

	Vector3(V3T X, V3T Y, V3T Z) : x(X), y(Y), z(Z) {}

	Vector3 operator+(Vector3<V3T> v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3<V3T> v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(Vector3<V3T> v)
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	V3T Normalize()
	{
		return (V3T)std::sqrt(x*x + y*y + z*z);
	}

	V3T Dot(Vector3<V3T> v)
	{
		return (V3T)x * v.x + y * v.y + z * v.z;
	}

	Vector3 Cross(Vector3<V3T> v)
	{
		Vector3 cross;
		cross.x = y * v.z - z * v.y;
		cross.y = z * v.x - x * v.z;
		cross.z = x * v.y - y * v.x;
		return cross;
	}
};
#endif