#pragma once
#include <vector>
class ThomasAlgorithm
{
	private:
		double aCoef;
		double bCoef;
		double cCoef;
		int size;
	public:
		ThomasAlgorithm(); //default constructor
		ThomasAlgorithm(double a, double b, double c,int size);
		void setCoefficients(double newA, double newB, double newC);
		void setSize(int newSize);
		std::vector<double> solve(std::vector<double> dVector);
};