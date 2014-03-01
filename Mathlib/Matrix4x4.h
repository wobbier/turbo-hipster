#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector3.h"

#define M(col,row) (row*4)+col

class Matrix4x4 {
public:
	/// 0 4  8 12   [0][0] [1][0] [2][0] [3][0]   
	/// 1 5  9 13   [0][1] [1][1] [2][1] [3][1]
	/// 2 6 10 14   [0][2] [1][2] [2][2] [3][2]
	/// 3 7 11 15   [0][3] [1][3] [2][3] [3][3]
	float m[16];

	Matrix4x4();

	Matrix4x4(float xx, float xy, float xz, float xw,
		float yx, float yy, float yz, float yw,
		float zx, float zy, float zz, float zw,
		float wx, float wy, float wz, float ww);

	Matrix4x4 operator+(Matrix4x4 rhs);

	Matrix4x4 operator-(Matrix4x4 rhs);

	Matrix4x4 operator*(float scalar);

	Matrix4x4 operator*(const Matrix4x4& rhs);

	Matrix4x4& operator*=(const Matrix4x4& n);
	
	float& operator()(size_t row, size_t col);

	float& operator[](int index);

	const float operator[](int index) const;

	static Matrix4x4 Identity();

	Matrix4x4 Inverse();

	static Matrix4x4 Translate(Vector3<float> position);

	static Matrix4x4 Rotate(Vector3<float> axis, float radians);

	void Clear();

	void Print();
};

#endif