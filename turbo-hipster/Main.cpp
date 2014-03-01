
#include <iostream>
#include "Matrix4x4.h"
#include <glut.h>

int main()
{
	Matrix4x4 matrix;
	matrix = Matrix4x4(2,3,1,5,1,0,3,1,0,2,-3,2,0,2,3,1);
	matrix.Print();
	Matrix4x4 identityFinal;
	identityFinal = Matrix4x4::Identity();
	//identityFinal *= Matrix4x4::Translate(Vector3<float>(10, 20, 5));
	identityFinal *= Matrix4x4::Rotate(Vector3<float>(0,0,1), (270 / 180) * 3.14159f);
	identityFinal.Print();
	for (;;){}
	return 0;
}