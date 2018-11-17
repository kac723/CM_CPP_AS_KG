#ifndef MATRIX_H //Include guard
#define MATRIX_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

/**
A Matrix class in order to sole the problem with the explicit method
The Matrix class provides:
* basic constructors for using the matrix method with the vector Class.
*
*/
class Matrix : private vector<vector<double>>
{
private:
	typedef vector<vector<double>> m;
public:
	using m::operator[];
	Matrix();
	Matrix(int rows, int col);
	Matrix(const Matrix& copyM);
	double oneNorm();
	double twoNorm();
	double uniformNorm();
	int getCols() const;
	int getRows() const;
	Matrix operator-(Matrix subtractMatrix);
};

#endif