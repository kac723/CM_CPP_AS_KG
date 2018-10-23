#pragma once
#include <vector>

class Matrix : private std::vector<std::vector<double> > 
{
	private:
		typedef std::vector<std::vector<double> > m;
	public:
		using m::operator[];
		Matrix();
		Matrix(int N);
		Matrix(int rows, int col);
		Matrix(Matrix& copyM);
		double oneNorm();
		double twoNorm();
		double uniformNorm();
		int getCols();
		int getRows();
		Matrix& operator-(const Matrix& subtractMatrix);
};