﻿#include "myMath.h"
#include "Novice.h"

#pragma region Vector2
Vector2 Vector2::operator+(const Vector2& target)
{
	return { x + target.x, y + target.y };
}

Vector2 Vector2::operator-(const Vector2& target)
{
	return { x - target.x, y - target.y };
}

Vector2 Vector2::operator*(const Vector2& target)
{
	return { x * target.x, y * target.y };
}

Vector2 Vector2::operator/(const Vector2& target)
{
	return { x / target.x, y / target.y };
}

Vector2 Vector2::operator*(const float& target)
{
	return { x * target, y * target };
}

Vector2 operator*(float scalar, const Vector2& vec)
{
	return { vec.x * scalar, vec.y * scalar };
}

Vector2 Vector2::operator/(const float& target)
{
	return { x / target, y / target };
}



Vector2 Vector2::operator*(const int& target)
{
	return { x * (float)target, y * (float)target };
}

Vector2 operator*(int scalar, const Vector2& vec)
{
	return { vec.x * (float)scalar, vec.y * (float)scalar };
}
#pragma endregion

#pragma region Vector3
Vector3 Vector3::operator+(const Vector3& target)
{
	return { x + target.x, y + target.y , z + target.z };
}

Vector3 Vector3::operator-(const Vector3& target)
{
	return { x - target.x, y - target.y , z - target.z };
}

Vector3 Vector3::operator*(const Vector3& target)
{
	return { x * target.x, y * target.y };
}

Vector3 Vector3::operator/(const Vector3& target)
{
	return { x / target.x, y / target.y, z / target.z };
}

Vector3 Vector3::operator*(const float& target)
{
	return { x * target, y * target, z * target };
}

Vector3 operator*(float scalar, const Vector3& vec)
{
	return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

Vector3 Vector3::operator/(const float& target)
{
	return { x / target, y / target, z / target };
}



Vector3 Vector3::operator*(const int& target)
{
	return { x * (float)target, y * (float)target, z * (float)target };
}


Vector3 operator*(int scalar, const Vector3& vec)
{
	return { vec.x * (float)scalar, vec.y * (float)scalar , vec.z * (float)scalar };
}

Vector3 Vector3::helmholtz()
{
	return { sqrtf(x * x),sqrtf(y * y),sqrtf(z * z) };
}

Vector3 Vector3::normalize()
{
	Vector3 length = helmholtz();
	if (length.x != 0 && length.y != 0 && length.z != 0) {
		return { x / length.x, y / length.y, z / length.z };
	}
	return Vector3();
}

Vector3 Add(const Vector3& V1, const Vector3& V2) {
	return { V1.x + V2.x, V1.y + V2.y , V1.z + V2.z };
}

Vector3 Subtract(const Vector3& V1, const Vector3& V2) {
	return { V1.x - V2.x, V1.y - V2.y , V1.z - V2.z };
}

Vector3 Multiply(const float& scalar, const Vector3& v) {
	return { scalar * v.x, scalar * v.y, scalar * v.z };
}

float Dot(const Vector3& V1, const Vector3& V2) {
	return V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
}

float Length(const Vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v) {
	float length = Length(v);
	if (length != 0) {
		return { v.x / length, v.y / length, v.z / length };
	}
	return Vector3();
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	static const int kColumnWidth = 60;
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

#pragma endregion

#pragma region Matrix3x3
Matrix3x3 Matrix3x3::operator+(const Matrix3x3& target)
{
	Matrix3x3 resuit = {};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			resuit.m[i][j] = m[i][j] + target.m[i][j];
		}
	}

	return resuit;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& target)
{
	Matrix3x3 resuit = {};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			resuit.m[i][j] = m[i][j] - target.m[i][j];
		}
	}

	return resuit;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& target)
{
	Matrix3x3 result = {};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += m[i][k] * target.m[k][j];
			}
		}
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////陣列変換

Matrix3x3 MakeTranslateMatrix3x3(const Vector2 translate) {
	return { 1,0,0,
			 0,1,0,
			  translate.x,translate.y,1 };
}

Vector2 MakeTranslateVector2(const Matrix3x3 translate) {
	return { translate.m[2][0],translate.m[2][1] };
}

////////////////////////////////////////////////////////////////////////////陣列計算

Vector2 Vector2xMatrix3x3(const Vector2 vector, const Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 MakeRotateMatrix(const float theta) {
	return{ cosf(theta) ,sinf(theta),0,
			-sinf(theta),cosf(theta),0,
			0,0,1 };
}

Matrix3x3 Inverse(Matrix3x3 matrix) {
	float determinant = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1])
		-
		(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] +
			matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] +
			matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	return Matrix3x3{ (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / determinant,
					 -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) / determinant,
					  (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / determinant,

					 -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) / determinant,
					  (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / determinant,
					 -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) / determinant,

					  (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / determinant,
					 -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) / determinant,
					  (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / determinant };
}


Matrix3x3 Transpose(Matrix3x3 matrix) {

	return Matrix3x3{ matrix.m[0][0],matrix.m[1][0],matrix.m[2][0],
					  matrix.m[0][1],matrix.m[1][1],matrix.m[2][1],
					  matrix.m[0][2],matrix.m[1][2],matrix.m[2][2] };
}

////////////////////////////////////////////////////////////////////////////陣列表示

//void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
//	int kColumnWidth = 80;
//	int kRowHeight = 40;
//	for (int row = 0; row < 3; ++row) {
//		for (int column = 0; column < 3; ++column) {
//			Novice::ScreenPrintf(
//				x + column * kColumnWidth,
//				y + row * kRowHeight,
//				"%.02f",
//				matrix.m[row][column]
//			);
//		}
//	}
//}

////////////////////////////////////////////////////////////////////////////陣列結合

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	return { scale.x * cosf(rotate),scale.x * sinf(rotate),0,
			 -scale.y * sinf(rotate),scale.y * cosf(rotate),0,
			  translate.x,translate.y,1 };
}

Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	Matrix3x3 result = matrix1 * matrix2;
	return result;
}

Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3)
{
	Matrix3x3 result = matrix1 * matrix2 * matrix3;
	return result;
}

Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3, Matrix3x3 matrix4)
{
	Matrix3x3 result = matrix1 * matrix2 * matrix3 * matrix4;
	return result;
}

////////////////////////////////////////////////////////////////////////////world改変陣列

Matrix3x3 MakeWorldMatrix(Matrix3x3 origin) {
	return origin;
}

Matrix3x3 MakeViewMatrix(Matrix3x3 origin, Vector2 pos)
{
	Vector2 move = pos;
	Matrix3x3 move2 = MakeTranslateMatrix3x3(move);
	Matrix3x3 result = MatrixMix(origin, move2);
	return Inverse(result);
}

Matrix3x3 MakeOrthographicMatrix(Vector2 leftTop, Vector2 rightBottom)
{
	return{ 2.0f / (rightBottom.x - leftTop.x),0.0f,0.0f,
			0.0f,2.0f / (leftTop.y - rightBottom.y),0.0f,
			(leftTop.x + rightBottom.x) / (leftTop.x - rightBottom.x),(leftTop.y + rightBottom.y) / (rightBottom.y - leftTop.y),1.0f };
}

Matrix3x3 MakeViewportMatrix(Vector2 leftTop, Vector2 rightBottom)
{
	return{ rightBottom.x / 2.0f,0.0f,0.0f,
			0.0f,-(rightBottom.y / 2.0f),0.0f,
			leftTop.x + (rightBottom.x / 2.0f),leftTop.y + (rightBottom.y / 2.0f),1.0f };
}
#pragma endregion

#pragma region Matrix4x4
Matrix4x4 Matrix4x4::Identity()
{
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			resuit.m[i][j] = 0;
			m[i][j] = 0;
			if (i == j) {
				resuit.m[i][j] = 1;
				m[i][j] = 1;
			}
		}
	}
	return resuit;
}

Matrix4x4 Matrix4x4::Inverse() {
	float determinant = m[0][0] * m[1][1] * m[2][2] * m[3][3]
					  + m[0][0] * m[1][2] * m[2][3] * m[3][1]
					  + m[0][0] * m[1][3] * m[2][1] * m[3][2]
					  
					  - m[0][0] * m[1][3] * m[2][2] * m[3][1]
					  - m[0][0] * m[1][2] * m[2][1] * m[3][3]
					  - m[0][0] * m[1][1] * m[2][3] * m[3][2]
					  
					  - m[0][1] * m[1][0] * m[2][2] * m[3][3]
					  - m[0][2] * m[1][0] * m[2][3] * m[3][1]
					  - m[0][3] * m[1][0] * m[2][1] * m[3][2]
					  
					  + m[0][3] * m[1][0] * m[2][2] * m[3][1]
					  + m[0][2] * m[1][0] * m[2][1] * m[3][3]
					  + m[0][1] * m[1][0] * m[2][3] * m[3][2]
					  
					  + m[0][1] * m[1][2] * m[2][0] * m[3][3]
					  + m[0][2] * m[1][3] * m[2][0] * m[3][1]
					  + m[0][3] * m[1][1] * m[2][0] * m[3][2]
					  
					  - m[0][3] * m[1][2] * m[2][0] * m[3][1]
					  - m[0][2] * m[1][1] * m[2][0] * m[3][3]
					  - m[0][1] * m[1][3] * m[2][0] * m[3][2]
					  
					  - m[0][1] * m[1][2] * m[2][3] * m[3][0]
					  - m[0][2] * m[1][3] * m[2][1] * m[3][0]
					  - m[0][3] * m[1][1] * m[2][2] * m[3][0]
					  
					  + m[0][3] * m[1][2] * m[2][1] * m[3][0]
					  + m[0][2] * m[1][1] * m[2][3] * m[3][0]
					  + m[0][1] * m[1][3] * m[2][2] * m[3][0];

	return Matrix4x4{ (m[1][1] * m[2][2] * m[3][3]
					 + m[1][2] * m[2][3] * m[3][1]
					 + m[1][3] * m[2][1] * m[3][2]
					 - m[1][3] * m[2][2] * m[3][1]
					 - m[1][2] * m[2][1] * m[3][3]
					 - m[1][1] * m[2][3] * m[3][2]) / determinant,/// 11

					(- m[0][1] * m[2][2] * m[3][3]
					 - m[0][2] * m[2][3] * m[3][1]
					 - m[0][3] * m[2][1] * m[3][2]
					 + m[0][3] * m[2][2] * m[3][1]
					 + m[0][2] * m[2][1] * m[3][3]
					 + m[0][1] * m[2][3] * m[3][2]) / determinant,/// 12

					(+ m[0][1] * m[1][2] * m[3][3]
					 + m[0][2] * m[1][3] * m[3][1]
					 + m[0][3] * m[1][1] * m[3][2]
					 - m[0][3] * m[1][2] * m[3][1]
					 - m[0][2] * m[1][1] * m[3][3]
					 - m[0][1] * m[1][3] * m[3][2]) / determinant,/// 13

					(- m[0][1] * m[1][2] * m[2][3]
					 - m[0][2] * m[1][3] * m[2][1]
					 - m[0][3] * m[1][1] * m[2][2]
					 + m[0][3] * m[1][2] * m[2][1]
					 + m[0][2] * m[1][1] * m[2][3]
					 + m[0][1] * m[1][3] * m[2][2]) / determinant,/// 14

					(- m[1][0] * m[2][2] * m[3][3]
					 - m[1][2] * m[2][3] * m[3][0]
					 - m[1][3] * m[2][0] * m[3][2]
					 + m[1][3] * m[2][2] * m[3][0]
					 + m[1][2] * m[2][0] * m[3][3]
					 + m[1][0] * m[2][3] * m[3][2]) / determinant,/// 21

					(+ m[0][0] * m[2][2] * m[3][3]
					 + m[0][2] * m[2][3] * m[3][0]
					 + m[0][3] * m[2][0] * m[3][2]
					 - m[0][3] * m[2][2] * m[3][0]
					 - m[0][2] * m[2][0] * m[3][3]
					 - m[0][0] * m[2][3] * m[3][2]) / determinant,/// 22

					(- m[0][0] * m[1][2] * m[3][3]
					 - m[0][2] * m[1][3] * m[3][0]
					 - m[0][3] * m[1][0] * m[3][2]
					 + m[0][3] * m[1][2] * m[3][0]
					 + m[0][2] * m[1][0] * m[3][3]
					 + m[0][0] * m[1][3] * m[3][2]) / determinant,/// 23

					(+ m[0][0] * m[1][2] * m[2][3]
					 + m[0][2] * m[1][3] * m[2][0]
					 + m[0][3] * m[1][0] * m[2][2]
					 - m[0][3] * m[1][2] * m[2][0]
					 - m[0][2] * m[1][0] * m[2][3]
					 - m[0][0] * m[1][3] * m[2][2]) / determinant,/// 24

					(+ m[1][0] * m[2][1] * m[3][3]
					 + m[1][1] * m[2][3] * m[3][0]
					 + m[1][3] * m[2][0] * m[3][1]
					 - m[1][3] * m[2][1] * m[3][0]
					 - m[1][1] * m[2][0] * m[3][3]
					 - m[1][0] * m[2][3] * m[3][1]) / determinant,/// 31

					(- m[0][0] * m[2][1] * m[3][3]
					 - m[0][1] * m[2][3] * m[3][0]
					 - m[0][3] * m[2][0] * m[3][1]
					 + m[0][3] * m[2][1] * m[3][0]
					 + m[0][1] * m[2][0] * m[3][3]
					 + m[0][0] * m[2][3] * m[3][1]) / determinant,/// 32

					(+ m[0][0] * m[1][1] * m[3][3]
					 + m[0][1] * m[1][3] * m[3][0]
					 + m[0][3] * m[1][0] * m[3][1]
					 - m[0][3] * m[1][1] * m[3][0]
					 - m[0][1] * m[1][0] * m[3][3]
					 - m[0][0] * m[1][3] * m[3][1]) / determinant,/// 33

					(- m[0][0] * m[1][1] * m[2][3]
					 - m[0][1] * m[1][3] * m[2][0]
					 - m[0][3] * m[1][0] * m[2][1]
					 + m[0][3] * m[1][1] * m[2][0]
					 + m[0][1] * m[1][0] * m[2][3]
					 + m[0][0] * m[1][3] * m[2][1]) / determinant,/// 34

					(- m[1][0] * m[2][1] * m[3][2]
					 - m[1][1] * m[2][2] * m[3][0]
					 - m[1][2] * m[2][0] * m[3][1]
					 + m[1][2] * m[2][1] * m[3][0]
					 + m[1][1] * m[2][0] * m[3][2]
					 + m[1][0] * m[2][2] * m[3][1]) / determinant,/// 41

					(+ m[0][0] * m[2][1] * m[3][2]
					 + m[0][1] * m[2][2] * m[3][0]
					 + m[0][2] * m[2][0] * m[3][1]
					 - m[0][2] * m[2][1] * m[3][0]
					 - m[0][1] * m[2][0] * m[3][2]
					 - m[0][0] * m[2][2] * m[3][1]) / determinant,/// 42

					(- m[0][0] * m[1][1] * m[3][2]
					 - m[0][1] * m[1][2] * m[3][0]
					 - m[0][2] * m[1][0] * m[3][1]
					 + m[0][2] * m[1][1] * m[3][0]
					 + m[0][1] * m[1][0] * m[3][2]
					 + m[0][0] * m[1][2] * m[3][1]) / determinant,/// 43

					(+ m[0][0] * m[1][1] * m[2][2]
					 + m[0][1] * m[1][2] * m[2][0]
					 + m[0][2] * m[1][0] * m[2][1]
					 - m[0][2] * m[1][1] * m[2][0]
					 - m[0][1] * m[1][0] * m[2][2]
					 - m[0][0] * m[1][2] * m[2][1]) / determinant /// 44
	};
}

Matrix4x4 Matrix4x4::Transpose()
{
	Matrix4x4 result = {};
	Matrix4x4 a = *this;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = a.m[j][i];
			m[i][j] = a.m[j][i];

		}
	}
	return result;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& target)
{
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m[x][y] + target.m[x][y];
		}
	}


	return resuit;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& target)
{
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m[x][y] - target.m[x][y];
		}
	}
	return resuit;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& target)
{
	//Matrix3x3 result = {};
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		for (int k = 0; k < 3; k++) {
	//			result.m[i][j] += m[i][k] * target.m[k][j];
	//		}
	//	}
	//}
	//return result;

	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				resuit.m[i][j] += m[i][k] * target.m[k][j];
			}
		}
	}
	return resuit;
}

Matrix4x4 Matrix4x4::operator*(const float& target)
{
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m[x][y] * target;
		}
	}
	return resuit;
}


Matrix4x4 operator*(float scalar, const Matrix4x4& vec)
{
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = vec.m[x][y] * scalar;
		}
	}
	return resuit;
}

#pragma region 陣列転換
Matrix4x4 MakeTranslateMatrix3x3(const Vector3 translate)
{
	return Matrix4x4{		 1.0f,		  0.0f,		   0.0f, 0.0f,
							 0.0f,		  1.0f,		   0.0f, 0.0f,
							 0.0f,		  0.0f,		   1.0f, 0.0f,
					  translate.x, translate.y,	translate.z, 1.0f };
}

Vector3 MakeTranslateVector3(const Matrix4x4 translate)
{
	return Vector3(translate.m[3][0],translate.m[3][1],translate.m[3][2]);
}
#pragma endregion

//////////////////////////////////////////////////////////////////////////陣列表示

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m1.m[x][y] + m2.m[x][y];
		}
	}
	return resuit;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m1.m[x][y] - m2.m[x][y];
		}
	}
	return resuit;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				resuit.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return resuit;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	float determinant = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	return Matrix4x4{ (m.m[1][1] * m.m[2][2] * m.m[3][3]
					 + m.m[1][2] * m.m[2][3] * m.m[3][1]
					 + m.m[1][3] * m.m[2][1] * m.m[3][2]
					 - m.m[1][3] * m.m[2][2] * m.m[3][1]
					 - m.m[1][2] * m.m[2][1] * m.m[3][3]
					 - m.m[1][1] * m.m[2][3] * m.m[3][2]) / determinant,/// 11

					(-m.m[0][1] * m.m[2][2] * m.m[3][3]
					 - m.m[0][2] * m.m[2][3] * m.m[3][1]
					 - m.m[0][3] * m.m[2][1] * m.m[3][2]
					 + m.m[0][3] * m.m[2][2] * m.m[3][1]
					 + m.m[0][2] * m.m[2][1] * m.m[3][3]
					 + m.m[0][1] * m.m[2][3] * m.m[3][2]) / determinant,/// 12

					(+m.m[0][1] * m.m[1][2] * m.m[3][3]
					 + m.m[0][2] * m.m[1][3] * m.m[3][1]
					 + m.m[0][3] * m.m[1][1] * m.m[3][2]
					 - m.m[0][3] * m.m[1][2] * m.m[3][1]
					 - m.m[0][2] * m.m[1][1] * m.m[3][3]
					 - m.m[0][1] * m.m[1][3] * m.m[3][2]) / determinant,/// 13

					(-m.m[0][1] * m.m[1][2] * m.m[2][3]
					 - m.m[0][2] * m.m[1][3] * m.m[2][1]
					 - m.m[0][3] * m.m[1][1] * m.m[2][2]
					 + m.m[0][3] * m.m[1][2] * m.m[2][1]
					 + m.m[0][2] * m.m[1][1] * m.m[2][3]
					 + m.m[0][1] * m.m[1][3] * m.m[2][2]) / determinant,/// 14

					(-m.m[1][0] * m.m[2][2] * m.m[3][3]
					 - m.m[1][2] * m.m[2][3] * m.m[3][0]
					 - m.m[1][3] * m.m[2][0] * m.m[3][2]
					 + m.m[1][3] * m.m[2][2] * m.m[3][0]
					 + m.m[1][2] * m.m[2][0] * m.m[3][3]
					 + m.m[1][0] * m.m[2][3] * m.m[3][2]) / determinant,/// 21

					(+m.m[0][0] * m.m[2][2] * m.m[3][3]
					 + m.m[0][2] * m.m[2][3] * m.m[3][0]
					 + m.m[0][3] * m.m[2][0] * m.m[3][2]
					 - m.m[0][3] * m.m[2][2] * m.m[3][0]
					 - m.m[0][2] * m.m[2][0] * m.m[3][3]
					 - m.m[0][0] * m.m[2][3] * m.m[3][2]) / determinant,/// 22

					(-m.m[0][0] * m.m[1][2] * m.m[3][3]
					 - m.m[0][2] * m.m[1][3] * m.m[3][0]
					 - m.m[0][3] * m.m[1][0] * m.m[3][2]
					 + m.m[0][3] * m.m[1][2] * m.m[3][0]
					 + m.m[0][2] * m.m[1][0] * m.m[3][3]
					 + m.m[0][0] * m.m[1][3] * m.m[3][2]) / determinant,/// 23

					(+m.m[0][0] * m.m[1][2] * m.m[2][3]
					 + m.m[0][2] * m.m[1][3] * m.m[2][0]
					 + m.m[0][3] * m.m[1][0] * m.m[2][2]
					 - m.m[0][3] * m.m[1][2] * m.m[2][0]
					 - m.m[0][2] * m.m[1][0] * m.m[2][3]
					 - m.m[0][0] * m.m[1][3] * m.m[2][2]) / determinant,/// 24

					(+m.m[1][0] * m.m[2][1] * m.m[3][3]
					 + m.m[1][1] * m.m[2][3] * m.m[3][0]
					 + m.m[1][3] * m.m[2][0] * m.m[3][1]
					 - m.m[1][3] * m.m[2][1] * m.m[3][0]
					 - m.m[1][1] * m.m[2][0] * m.m[3][3]
					 - m.m[1][0] * m.m[2][3] * m.m[3][1]) / determinant,/// 31

					(-m.m[0][0] * m.m[2][1] * m.m[3][3]
					 - m.m[0][1] * m.m[2][3] * m.m[3][0]
					 - m.m[0][3] * m.m[2][0] * m.m[3][1]
					 + m.m[0][3] * m.m[2][1] * m.m[3][0]
					 + m.m[0][1] * m.m[2][0] * m.m[3][3]
					 + m.m[0][0] * m.m[2][3] * m.m[3][1]) / determinant,/// 32

					(+m.m[0][0] * m.m[1][1] * m.m[3][3]
					 + m.m[0][1] * m.m[1][3] * m.m[3][0]
					 + m.m[0][3] * m.m[1][0] * m.m[3][1]
					 - m.m[0][3] * m.m[1][1] * m.m[3][0]
					 - m.m[0][1] * m.m[1][0] * m.m[3][3]
					 - m.m[0][0] * m.m[1][3] * m.m[3][1]) / determinant,/// 33

					(-m.m[0][0] * m.m[1][1] * m.m[2][3]
					 - m.m[0][1] * m.m[1][3] * m.m[2][0]
					 - m.m[0][3] * m.m[1][0] * m.m[2][1]
					 + m.m[0][3] * m.m[1][1] * m.m[2][0]
					 + m.m[0][1] * m.m[1][0] * m.m[2][3]
					 + m.m[0][0] * m.m[1][3] * m.m[2][1]) / determinant,/// 34

					(-m.m[1][0] * m.m[2][1] * m.m[3][2]
					 - m.m[1][1] * m.m[2][2] * m.m[3][0]
					 - m.m[1][2] * m.m[2][0] * m.m[3][1]
					 + m.m[1][2] * m.m[2][1] * m.m[3][0]
					 + m.m[1][1] * m.m[2][0] * m.m[3][2]
					 + m.m[1][0] * m.m[2][2] * m.m[3][1]) / determinant,/// 41

					(+m.m[0][0] * m.m[2][1] * m.m[3][2]
					 + m.m[0][1] * m.m[2][2] * m.m[3][0]
					 + m.m[0][2] * m.m[2][0] * m.m[3][1]
					 - m.m[0][2] * m.m[2][1] * m.m[3][0]
					 - m.m[0][1] * m.m[2][0] * m.m[3][2]
					 - m.m[0][0] * m.m[2][2] * m.m[3][1]) / determinant,/// 42

					(-m.m[0][0] * m.m[1][1] * m.m[3][2]
					 - m.m[0][1] * m.m[1][2] * m.m[3][0]
					 - m.m[0][2] * m.m[1][0] * m.m[3][1]
					 + m.m[0][2] * m.m[1][1] * m.m[3][0]
					 + m.m[0][1] * m.m[1][0] * m.m[3][2]
					 + m.m[0][0] * m.m[1][2] * m.m[3][1]) / determinant,/// 43

					(+m.m[0][0] * m.m[1][1] * m.m[2][2]
					 + m.m[0][1] * m.m[1][2] * m.m[2][0]
					 + m.m[0][2] * m.m[1][0] * m.m[2][1]
					 - m.m[0][2] * m.m[1][1] * m.m[2][0]
					 - m.m[0][1] * m.m[1][0] * m.m[2][2]
					 - m.m[0][0] * m.m[1][2] * m.m[2][1]) / determinant /// 44
	};

}

Matrix4x4 Transpose(Matrix4x4 m) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}


Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			resuit.m[i][j] = 0;
			if (i == j) {
				resuit.m[i][j] = 1;
			}
		}
	}
	return resuit;
}

void MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* name) {
	int kColumnWidth = 60;
	int kRowHeight = 20;
	if (name == nullptr) {
		for (int row = 0; row < 4; ++row) {
			for (int column = 0; column < 4; ++column) {
				Novice::ScreenPrintf(
					x + column * kColumnWidth,
					y + row * kRowHeight,
					"%6.02f",
					matrix.m[row][column]
				);
			}
		}
	} else {
		Novice::ScreenPrintf(x, y, "%s", name);
		for (int row = 0; row < 4; ++row) {
			for (int column = 0; column < 4; ++column) {
				Novice::ScreenPrintf(
					x + column * kColumnWidth,
					y + row * kRowHeight + kRowHeight,
					"%6.02f",
					matrix.m[row][column]
				);
			}
		}
	}
}

Matrix4x4 MakeScaleMatrix(const Vector3 scole)
{
	return Matrix4x4{ scole.x,    0.0f,    0.0f, 0.0f,
						 0.0f, scole.y,    0.0f, 0.0f,
					     0.0f,    0.0f, scole.z, 0.0f,
					     0.0f,    0.0f,	   0.0f, 1.0f };
}

Matrix4x4 MakeRotateXMatrix(const float theta) {
	Matrix4x4 rX = {		1.0f,		   0.0f,         0.0f, 0.0f,
							0.0f,   cosf(theta),  sinf(theta), 0.0f,
							0.0f,  -sinf(theta),  cosf(theta), 0.0f,
							0.0f,	       0.0f,		 0.0f, 1.0f };
	return rX;
}

Matrix4x4 MakeRotateYMatrix(const float theta) {
	Matrix4x4 rY = { cosf(theta),		   0.0f, -sinf(theta), 0.0f,
							0.0f,		   1.0f,         0.0f, 0.0f,
					 sinf(theta),		   0.0f,  cosf(theta), 0.0f,
							0.0f,		   0.0f,		 0.0f, 1.0f };
	return rY;
}

Matrix4x4 MakeRotateZMatrix(const float theta) {
	Matrix4x4 rZ = { cosf(theta),   sinf(theta),		 0.0f, 0.0f,
					-sinf(theta),   cosf(theta),		 0.0f, 0.0f,
							0.0f,   	   0.0f,		 1.0f, 0.0f,
							0.0f,   	   0.0f,		 0.0f, 1.0f };
	return rZ;
}

Matrix4x4 MakeRotateMatrix(const Matrix4x4 thetaX, const Matrix4x4 thetaY, const Matrix4x4 thetaZ) {
	return Multiply(thetaX, Multiply(thetaY,thetaZ));
}



Matrix4x4 MakeTranslateMatrix(const Vector3 translate)
{
	return Matrix4x4{		 1.0f,		  0.0f,		   0.0f, 0.0f,
							 0.0f,		  1.0f,		   0.0f, 0.0f,
							 0.0f,		  0.0f,		   1.0f, 0.0f,
					  translate.x, translate.y,	translate.z, 1.0f };
}

Matrix4x4 MakeAffineMatrix(Vector3 scole, Vector3 rotate, Vector3 translate)
{
	Matrix4x4 r1 = MakeScaleMatrix(scole);

	Matrix4x4 r2 = MakeRotateMatrix(MakeRotateXMatrix(rotate.x),
									MakeRotateYMatrix(rotate.y),
									MakeRotateZMatrix(rotate.z));

	Matrix4x4 r3 = MakeTranslateMatrix(translate);

	return Matrix4x4{ r1 * (r2 * r3) };
}


Matrix4x4 MatrixMix(Matrix4x4* matrix1, Matrix4x4* matrix2, Matrix4x4* matrix3, Matrix4x4* matrix4)
{
		 if (matrix4 == nullptr) { return Matrix4x4{ *matrix1 * *matrix2 * *matrix3 }; }
	else if (matrix3 == nullptr) { return Matrix4x4{ *matrix1 * *matrix2 }; }
	   else						 { return Matrix4x4{ *matrix1 * *matrix2 * *matrix3 * *matrix4 }; }
}

/////////////////////////////////////////////////////////////////

Matrix4x4 MakeWorldMatrix(Matrix4x4 origin)
{
		return origin;
}

Matrix4x4 MakeViewMatrix(Vector3 scole, Vector3 rotate, Vector3 translate)
{
	return MakeAffineMatrix( scole, rotate, translate);
}

Matrix4x4 MakeProjectionMatrix(float leftO, float rightO, float topO, float bottomO, float nearO, float farO)
{
	return{ 2.0f / (rightO - leftO),0.0f,0.0f,0.0f,
			0.0f,2.0f / (topO - bottomO),0.0f,0.0f,
			0.0f,0.0f,1.0f / (farO - nearO),0.0f,
			(leftO + rightO) / (leftO - rightO),(topO + bottomO) / (bottomO - topO),nearO / (nearO - farO),1.0f };
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	return { (1.0f / aspectRatio) * 1.0f / tanf( fovY / 2.0f),0.0f,0.0f,0.0f,
			 0.0f,1.0f /tanf(fovY / 2.0f ),0.0f,0.0f,
			 0.0f,0.0f,farClip / (farClip - nearClip),1.0f,
			 0.0f,0.0f,-(nearClip * farClip) / (farClip - nearClip),0.0f };
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float maxD, float minD)
{
	return { width / 2.0f,0.0f,0.0f,0.0f,
			 0.0f,-(height / 2.0f),0.0f,0.0f,
			 0.0f,0.0f,maxD - minD,0.0f,
			 left + (width / 2.0f),top + (height / 2.0f),minD,1.0f };
}

Vector3 viewFinilTransform(Vector3 obj, Matrix4x4 tranformMatrix) {
	return MakeTranslateVector3(MakeTranslateMatrix(obj) * tranformMatrix);
}


//////////////////////////////////////////////////////////////////////////陣列結合

#pragma endregion

#pragma region Other
bool binaryComparator(int binary, int target) {
	if (binary == (target & binary)) {
		return true;
	}
	return false;
}
#pragma endregion

