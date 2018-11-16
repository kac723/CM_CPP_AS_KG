#ifndef THOMASALGORITHM_H //Include guard
#define THOMASALGORITHM_H

#include <vector>

using namespace std;

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
		vector<double> solve(vector<double> dVector);
};

#endif