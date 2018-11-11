#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
class Matrix : private std::vector<std::vector<double>>
{
private:
	typedef std::vector<std::vector<double>> m;
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