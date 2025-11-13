#include "Matrix.h"

Matrix::Matrix() = default;
Matrix::Matrix(float value) {
	data[0][0] = value;
	data[1][1] = value;
	data[2][2] = value;
	data[3][3] = (value == 0.0f ? 0.0f : 1.0f);
}
Matrix::~Matrix() {
	delete[] data;
}

void Matrix::translate(float x, float y, float z) {
	Matrix translation;
	translation.data[0][3] = x;
	translation.data[1][3] = y;
	translation.data[2][3] = z;
	Matrix result;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				result.data[i][j] += data[i][k] * translation.data[k][j];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] = result.data[i][j];
}
void Matrix::rotate(float radians) {
	Matrix rotation;
	rotation.data[0][0] = cos(radians);
	rotation.data[0][1] = -sin(radians);
	rotation.data[1][0] = sin(radians);
	rotation.data[1][1] = cos(radians);
	Matrix result = (*this) * rotation;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] = result.data[i][j];
}
void Matrix::scale(float x, float y, float z) {
	Matrix scale;
	scale.data[0][0] = x;
	scale.data[1][1] = y;
	scale.data[2][2] = z;
	Matrix result = (*this) * scale;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] = result.data[i][j];
}

void Matrix::clean() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (i == j)
				data[i][j] = 1.0f;
			else
				data[i][j] = 0.0f;
		}
}
void Matrix::print() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			std::cout << data[i][j] << (i * 4 + j == 15 ? "." : ", ") << (j == 3 ? "\n" : "");
}
float* Matrix::toArray() {
	float* result = new float[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i*4+j] = data[i][j];
		}
	}
	return result;
}

Matrix operator+(const Matrix& a, const Matrix& b) {
	Matrix result(0.0f);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.data[i][j] = a.data[i][j] + b.data[i][j];
	return result;
}
Matrix operator-(const Matrix& a, const Matrix& b) {
	Matrix result(0.0f);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.data[i][j] = a.data[i][j] - b.data[i][j];
	return result;
}
Matrix operator*(const Matrix& a, const Matrix& b) {
	Matrix result(0.0f);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				result.data[i][j] += a.data[i][k] * b.data[k][j];
	return result;
}
Matrix operator*(const Matrix& a, const float& b) {
	Matrix result(0.0f);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.data[i][j] = a.data[i][j] * b;
	return result;
}
float* operator*(const Matrix& a, const float b[4]) {
	float* result = new float[4] {0.0f, 0.0f, 0.0f, 0.0f};
	for (int i = 0; i < 4; i++)
		for (int k = 0; k < 4; k++)
			result[i] += a.data[i][k] * b[k];
	return result;
}