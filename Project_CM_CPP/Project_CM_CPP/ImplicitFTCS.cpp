#include "ImplicitFTCS.h"
#include <iterator>
using namespace std;
void ImplicitFTCS::calculateNumericalSolution()
{
	Matrix numericalCopy = this->getNumerical();
	vector<double> dTest(this->getVectorX().size());
	double a = this->getA();
	ThomasAlgorithm TA(-a/2, 1, a/2, this->getVectorX().size());
	vector<double> resultVector(this->getVectorX().size(), 0);
	for (int n = 1; n < this->getVectorT().size(); n++)
	{
		for (int i = 0; i < this->getVectorX().size(); i++)
		{
			dTest[i] = numericalCopy[i][n - 1];
		}
		resultVector=TA.solve(dTest);
		for (int i = 0; i < this->getVectorX().size(); i++)
		{
			numericalCopy[i][n] = resultVector[i];
		}
	}
	this->setNumerical(numericalCopy);
}

ImplicitFTCS::ImplicitFTCS() {} 

ImplicitFTCS::ImplicitFTCS(double dT, double dx) : Scheme(dT, dx)
{
	this->calculateNumericalSolution();
}
