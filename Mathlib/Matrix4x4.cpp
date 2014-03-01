#include "Matrix4x4.h"
#include <iostream>
#include <stdexcept>

Matrix4x4::Matrix4x4()
{

}

Matrix4x4::Matrix4x4(float xx, float xy, float xz, float xw,
	float yx, float yy, float yz, float yw,
	float zx, float zy, float zz, float zw,
	float wx, float wy, float wz, float ww)
{
	m[M(0, 0)] = xx; m[M(0, 1)] = xy; m[M(0, 2)] = xz; m[M(0, 3)] = xw;
	m[M(1, 0)] = yx; m[M(1, 1)] = yy; m[M(1, 2)] = yz; m[M(1, 3)] = yw;
	m[M(2, 0)] = zx; m[M(2, 1)] = zy; m[M(2, 2)] = zz; m[M(2, 3)] = zw;
	m[M(3, 0)] = wx; m[M(3, 1)] = wy; m[M(3, 2)] = wz; m[M(3, 3)] = ww;
}
/// 0 4  8 12   [0][0] [1][0] [2][0] [3][0]   
/// 1 5  9 13   [0][1] [1][1] [2][1] [3][1]
/// 2 6 10 14   [0][2] [1][2] [2][2] [3][2]
/// 3 7 11 15   [0][3] [1][3] [2][3] [3][3]
Matrix4x4 Matrix4x4::operator+(Matrix4x4 rhs)
{
	Matrix4x4 tempMatrix;
	for (size_t r = 0; r < 4; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			tempMatrix.m[M(r, c)] = m[M(r, c)] + rhs.m[M(r, c)];
		}
	}
	return tempMatrix;
}

Matrix4x4 Matrix4x4::operator-(Matrix4x4 rhs)
{
	Matrix4x4 tempMatrix;
	for (size_t r = 0; r < 4; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			tempMatrix.m[M(r, c)] = m[M(r, c)] - rhs.m[M(r, c)];
		}
	}
	return tempMatrix;
}

Matrix4x4 Matrix4x4::operator*(float scalar)
{
	Matrix4x4 tempMatrix;
	for (size_t i = 0; i < 16; i++)
	{
		tempMatrix.m[i] = m[i] * scalar;
	}
	return tempMatrix;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs)
{
	Matrix4x4 product;
#define N(row,col)  rhs[(col*4)+row]
#define P(row,col)  product[(col*4)+row]
	for (int i = 0; i < 4; i++) {
		float ai0 = m[M(i, 0)], ai1 = m[M(i, 1)], ai2 = m[M(i, 2)], ai3 = m[M(i, 3)];
		P(i, 0) = ai0 * N(0, 0) + ai1 * N(1, 0) + ai2 * N(2, 0) + ai3 * N(3, 0);
		P(i, 1) = ai0 * N(0, 1) + ai1 * N(1, 1) + ai2 * N(2, 1) + ai3 * N(3, 1);
		P(i, 2) = ai0 * N(0, 2) + ai1 * N(1, 2) + ai2 * N(2, 2) + ai3 * N(3, 2);
		P(i, 3) = ai0 * N(0, 3) + ai1 * N(1, 3) + ai2 * N(2, 3) + ai3 * N(3, 3);
	}
#undef N
#undef P
	return product;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& n){
	*this = *this * n;
	/// returns all 16 floats on the stack
	return *this;
}

float& Matrix4x4::operator()(size_t row, size_t col)
{
	return m[M(row, col)];
}

float& Matrix4x4::operator[](int index)
{
	return m[index];
}

const float Matrix4x4::operator[](int index) const
{
	return m[index];
}

Matrix4x4 Matrix4x4::Identity()
{
	return Matrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::Inverse()
{
	Matrix4x4 inverseMatrix;
	float determinant =
		m[M(0, 0)] * m[M(1, 1)] * m[M(2, 2)] * m[M(3, 3)] + m[M(0, 0)] * m[M(1, 2)] * m[M(2, 3)] * m[M(3, 1)] + m[M(0, 0)] * m[M(1, 3)] * m[M(2, 1)] * m[M(3, 2)] +
		m[M(0, 1)] * m[M(1, 0)] * m[M(2, 3)] * m[M(3, 2)] + m[M(0, 1)] * m[M(1, 2)] * m[M(2, 0)] * m[M(3, 3)] + m[M(0, 1)] * m[M(1, 3)] * m[M(2, 2)] * m[M(3, 0)] +
		m[M(0, 2)] * m[M(1, 0)] * m[M(2, 1)] * m[M(3, 3)] + m[M(0, 2)] * m[M(1, 1)] * m[M(2, 3)] * m[M(3, 0)] + m[M(0, 2)] * m[M(1, 3)] * m[M(2, 0)] * m[M(3, 1)] +
		m[M(0, 3)] * m[M(1, 0)] * m[M(2, 2)] * m[M(3, 1)] + m[M(0, 3)] * m[M(1, 1)] * m[M(2, 0)] * m[M(3, 2)] + m[M(0, 3)] * m[M(1, 2)] * m[M(2, 1)] * m[M(3, 0)] -
		m[M(0, 0)] * m[M(1, 1)] * m[M(2, 3)] * m[M(3, 2)] - m[M(0, 0)] * m[M(1, 2)] * m[M(2, 1)] * m[M(3, 3)] - m[M(0, 0)] * m[M(1, 3)] * m[M(2, 2)] * m[M(3, 1)] -
		m[M(0, 1)] * m[M(1, 0)] * m[M(2, 2)] * m[M(3, 3)] - m[M(0, 1)] * m[M(1, 2)] * m[M(2, 3)] * m[M(3, 0)] - m[M(0, 1)] * m[M(1, 3)] * m[M(2, 0)] * m[M(3, 2)] -
		m[M(0, 2)] * m[M(1, 0)] * m[M(2, 3)] * m[M(3, 1)] - m[M(0, 2)] * m[M(1, 1)] * m[M(2, 0)] * m[M(3, 3)] - m[M(0, 2)] * m[M(1, 3)] * m[M(2, 1)] * m[M(3, 0)] -
		m[M(0, 3)] * m[M(1, 0)] * m[M(2, 1)] * m[M(3, 2)] - m[M(0, 3)] * m[M(1, 1)] * m[M(2, 2)] * m[M(3, 0)] - m[M(0, 3)] * m[M(1, 2)] * m[M(2, 0)] * m[M(3, 1)];

	Matrix4x4 tempMatrix;
	tempMatrix[M(0, 0)] =
		m[M(1, 1)] * m[M(2, 2)] * m[M(3, 3)] + m[M(1, 2)] * m[M(2, 3)] * m[M(3, 1)] + m[M(1, 3)] * m[M(2, 1)] * m[M(3, 2)] -
		m[M(1, 1)] * m[M(2, 3)] * m[M(3, 2)] - m[M(1, 2)] * m[M(2, 1)] * m[M(3, 3)] - m[M(1, 3)] * m[M(2, 2)] * m[M(3, 1)];
	tempMatrix[M(0, 1)] =
		m[M(0, 1)] * m[M(2, 3)] * m[M(3, 2)] + m[M(0, 2)] * m[M(2, 1)] * m[M(3, 3)] + m[M(0, 3)] * m[M(2, 2)] * m[M(3, 1)] -
		m[M(0, 1)] * m[M(2, 2)] * m[M(3, 3)] - m[M(0, 2)] * m[M(2, 3)] * m[M(3, 1)] - m[M(0, 3)] * m[M(2, 1)] * m[M(3, 2)];
	tempMatrix[M(0, 2)] =
		m[M(0, 1)] * m[M(1, 2)] * m[M(3, 3)] + m[M(0, 2)] * m[M(1, 3)] * m[M(3, 1)] + m[M(0, 3)] * m[M(1, 1)] * m[M(3, 2)] -
		m[M(0, 1)] * m[M(1, 3)] * m[M(3, 2)] - m[M(0, 2)] * m[M(1, 1)] * m[M(3, 3)] - m[M(0, 3)] * m[M(1, 2)] * m[M(3, 1)];
	tempMatrix[M(0, 3)] =
		m[M(0, 1)] * m[M(1, 3)] * m[M(2, 2)] + m[M(0, 2)] * m[M(1, 1)] * m[M(2, 3)] + m[M(0, 3)] * m[M(1, 2)] * m[M(2, 1)] -
		m[M(0, 1)] * m[M(1, 2)] * m[M(2, 3)] - m[M(0, 2)] * m[M(1, 3)] * m[M(2, 1)] - m[M(0, 3)] * m[M(1, 1)] * m[M(2, 2)];
	tempMatrix[M(1, 0)] =
		m[M(1, 0)] * m[M(2, 3)] * m[M(3, 2)] + m[M(1, 2)] * m[M(2, 0)] * m[M(3, 3)] + m[M(1, 3)] * m[M(2, 2)] * m[M(3, 0)] -
		m[M(1, 0)] * m[M(2, 2)] * m[M(3, 3)] - m[M(1, 2)] * m[M(2, 3)] * m[M(3, 0)] - m[M(1, 3)] * m[M(2, 0)] * m[M(3, 2)];
	tempMatrix[M(1, 1)] =
		m[M(0, 0)] * m[M(2, 2)] * m[M(3, 3)] + m[M(0, 2)] * m[M(2, 3)] * m[M(3, 0)] + m[M(0, 3)] * m[M(2, 0)] * m[M(3, 2)] -
		m[M(0, 0)] * m[M(2, 3)] * m[M(3, 2)] - m[M(0, 2)] * m[M(2, 0)] * m[M(3, 3)] - m[M(0, 3)] * m[M(2, 2)] * m[M(3, 0)];
	tempMatrix[M(1, 2)] =
		m[M(0, 0)] * m[M(1, 3)] * m[M(3, 2)] + m[M(0, 2)] * m[M(1, 0)] * m[M(3, 3)] + m[M(0, 3)] * m[M(1, 2)] * m[M(3, 0)] -
		m[M(0, 0)] * m[M(1, 2)] * m[M(3, 3)] - m[M(0, 2)] * m[M(1, 3)] * m[M(3, 0)] - m[M(0, 3)] * m[M(1, 0)] * m[M(3, 2)];
	tempMatrix[M(1, 3)] = 
		m[M(0, 0)] * m[M(1, 2)] * m[M(2, 3)] + m[M(0, 2)] * m[M(1, 3)] * m[M(2, 0)] + m[M(0, 3)] * m[M(1, 0)] * m[M(2, 2)] -
		m[M(0, 0)] * m[M(1, 3)] * m[M(2, 2)] - m[M(0, 2)] * m[M(1, 0)] * m[M(2, 3)] - m[M(0, 3)] * m[M(1, 2)] * m[M(2, 0)];
	tempMatrix[M(2, 0)] =
		m[M(1, 0)] * m[M(2, 1)] * m[M(3, 3)] + m[M(1, 1)] * m[M(2, 3)] * m[M(3, 0)] + m[M(1, 3)] * m[M(2, 0)] * m[M(3, 1)] -
		m[M(1, 0)] * m[M(2, 3)] * m[M(3, 1)] - m[M(1, 1)] * m[M(2, 0)] * m[M(3, 3)] - m[M(1, 3)] * m[M(2, 1)] * m[M(3, 0)];
	tempMatrix[M(2, 1)] =
		m[M(0, 0)] * m[M(2, 3)] * m[M(3, 1)] + m[M(0, 1)] * m[M(2, 0)] * m[M(3, 3)] + m[M(0, 3)] * m[M(2, 1)] * m[M(3, 0)] -
		m[M(0, 0)] * m[M(2, 1)] * m[M(3, 3)] - m[M(0, 1)] * m[M(2, 3)] * m[M(3, 0)] - m[M(0, 3)] * m[M(2, 0)] * m[M(3, 1)];
	tempMatrix[M(2, 2)] =
		m[M(0, 0)] * m[M(1, 1)] * m[M(3, 3)] + m[M(0, 1)] * m[M(1, 3)] * m[M(3, 0)] + m[M(0, 3)] * m[M(1, 0)] * m[M(3, 1)] -
		m[M(0, 0)] * m[M(1, 3)] * m[M(3, 1)] - m[M(0, 1)] * m[M(1, 0)] * m[M(3, 3)] - m[M(0, 3)] * m[M(1, 1)] * m[M(3, 0)];
	tempMatrix[M(2, 3)] =
		m[M(0, 0)] * m[M(1, 3)] * m[M(2, 1)] + m[M(0, 1)] * m[M(1, 0)] * m[M(2, 3)] + m[M(0, 3)] * m[M(1, 1)] * m[M(2, 0)] -
		m[M(0, 0)] * m[M(1, 1)] * m[M(2, 3)] - m[M(0, 1)] * m[M(1, 3)] * m[M(2, 0)] - m[M(0, 3)] * m[M(1, 0)] * m[M(2, 1)];
	tempMatrix[M(3, 0)] =
		m[M(1, 0)] * m[M(2, 2)] * m[M(2, 1)] + m[M(1, 1)] * m[M(2, 0)] * m[M(3, 2)] + m[M(1, 2)] * m[M(2, 1)] * m[M(3, 0)] -
		m[M(1, 0)] * m[M(2, 1)] * m[M(3, 2)] - m[M(1, 1)] * m[M(2, 2)] * m[M(3, 0)] - m[M(1, 2)] * m[M(2, 0)] * m[M(3, 1)];
	tempMatrix[M(3, 1)] =
		m[M(0, 0)] * m[M(2, 1)] * m[M(3, 2)] + m[M(0, 1)] * m[M(2, 2)] * m[M(3, 0)] + m[M(0, 2)] * m[M(2, 0)] * m[M(3, 1)] -
		m[M(0, 0)] * m[M(2, 2)] * m[M(3, 1)] - m[M(0, 1)] * m[M(2, 0)] * m[M(3, 2)] - m[M(0, 2)] * m[M(2, 1)] * m[M(3, 0)];
	tempMatrix[M(3, 2)] =
		m[M(0, 0)] * m[M(1, 2)] * m[M(3, 1)] + m[M(0, 1)] * m[M(1, 0)] * m[M(3, 2)] + m[M(0, 2)] * m[M(1, 1)] * m[M(3, 0)] -
		m[M(0, 0)] * m[M(1, 1)] * m[M(3, 2)] - m[M(0, 1)] * m[M(1, 2)] * m[M(3, 0)] - m[M(0, 2)] * m[M(1, 0)] * m[M(3, 1)];
	tempMatrix[M(3, 3)] =
		m[M(0, 0)] * m[M(1, 1)] * m[M(2, 2)] + m[M(0, 1)] * m[M(1, 2)] * m[M(2, 0)] + m[M(0, 2)] * m[M(1, 0)] * m[M(2, 1)] -
		m[M(0, 0)] * m[M(1, 2)] * m[M(2, 1)] - m[M(0, 1)] * m[M(1, 0)] * m[M(2, 2)] - m[M(0, 2)] * m[M(1, 1)] * m[M(2, 0)];

	return tempMatrix * (1 / determinant);
}

Matrix4x4 Matrix4x4::Translate(Vector3<float> position)
{
	Matrix4x4 tempMatrix = Identity();
	tempMatrix(3, 0) = position.x;
	tempMatrix(3, 1) = position.y;
	tempMatrix(3, 2) = position.z;
	return tempMatrix;
}

Matrix4x4 Matrix4x4::Rotate(Vector3<float> rotAxis, float radians)
{
	float cosang, sinang, cosm;
	Matrix4x4 temp;
	rotAxis = rotAxis.Normalize();

	cosang = float(cos(radians));
	sinang = float(sin(radians));
	cosm = (1.0f - cosang);

	temp[0] = (rotAxis.x * rotAxis.x * cosm) + cosang;
	temp[1] = (rotAxis.x * rotAxis.y * cosm) + (rotAxis.z * sinang);
	temp[2] = (rotAxis.x * rotAxis.z * cosm) - (rotAxis.y * sinang);
	temp[3] = 0.0;
	temp[4] = (rotAxis.x * rotAxis.y * cosm) - (rotAxis.z * sinang);
	temp[5] = (rotAxis.y * rotAxis.y * cosm) + cosang;
	temp[6] = (rotAxis.y * rotAxis.z * cosm) + (rotAxis.x * sinang);
	temp[7] = 0.0;
	temp[8] = (rotAxis.x * rotAxis.z * cosm) + (rotAxis.y * sinang);
	temp[9] = (rotAxis.y * rotAxis.z * cosm) - (rotAxis.x * sinang);
	temp[10] = (rotAxis.z * rotAxis.z * cosm) + cosang;
	temp[11] = 0.0;
	temp[12] = 0.0;
	temp[13] = 0.0;
	temp[14] = 0.0;
	temp[15] = 1.0;
	return temp;
}

void Matrix4x4::Clear()
{
	for (size_t i = 0; i < 16; ++i)
	{
		m[i] = 0;
	}
}

void Matrix4x4::Print() {
	printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n\n",
		m[0], m[1], m[2], m[3],
		m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11],
		m[12], m[13], m[14], m[15]);
}