#pragma once
#include <vector>
class ThomasAlgorithm
{
	private:
		//std::vector<double> a;
		//std::vector<double> b;
		//std::vector<double> c;
		//std::vector<double> d;
		//std::vector<double> x;
		double aCoef;
		double bCoef;
		double cCoef;
		int size;
	public:
		ThomasAlgorithm(); //default constructor
		ThomasAlgorithm(double a, double b, double c,int size);
		double getACoef();
		double getBCoef();
		double getCCoef();
		int getSize();
		std::vector<double> solve(std::vector<double> dVector);
};