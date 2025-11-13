#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix {

public:
	//the data of the matrix. 
	float data[4][4]{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};
	//construct an identity matrix.
	Matrix();
	//construct a matrix in which the main diagonal's members are value
	Matrix(float value);
	//destructor; deletes dynamicly allocated memory
	~Matrix();
	//prints data into the console (4 lines)
	void print();

	//multiply this matrix by a scaling matrix with corresponding x, y, and z values
	void scale(float x, float y, float z);
	
	//multiply this matrix by a translation matrix with corresponding x, y, and z values
	void translate(float x, float y, float z);

	//multiply this matrix by a rotation matrix with corresponding rotation in radians
	void rotate(float radians);

	void clean();
	//returns data in the form of a length 16 float array. RETURNS A DYNAMICALLY ALLOCATED ARRAY. ALWAYS CALL delete[] AFTER USE.
	float* toArray();
};
//matrix scalar multiplication
Matrix operator*(const Matrix& a, const float& b);
//matrix addition
Matrix operator+(const Matrix& a, const Matrix& b);
//matrix subtraction
Matrix operator-(const Matrix& a, const Matrix& b);
//matrix multiplication
Matrix operator*(const Matrix& a, const Matrix& b);
//matrix multiplication on a float array size 4. RETURNS A DYNAMICALLY ALLOCATED ARRAY. ALWAYS CALL delete[] AFTER USE.
float* operator*(const Matrix& a, const float b[4]);

#endif