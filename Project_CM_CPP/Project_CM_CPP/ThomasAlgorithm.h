#pragma once
#include <vector>
class ThomasAlgorithm
{
	private:
		std::vector<double> a;
		std::vector<double> b;
		std::vector<double> c;
		std::vector<double> d;
		std::vector<double> x;
	public:
		ThomasAlgorithm(); //default constructor
		ThomasAlgorithm(double a, double b, double c, std::vector<double> dV, int size);
		std::vector<double> getX();
		void solve();
};