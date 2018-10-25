#include "ImplicitFTCS.h"

using namespace std;
void ImplicitFTCS::calculateNumericalSolution()
{
	Matrix numericalCopy = this->getNumerical();
	vector<double> dTest(this->getVectorX().size());
	double a = this->getA();
	for (int n = 1; n < this->getVectorT().size(); n++)
	{
		for (int i = 0; i < this->getVectorX().size(); i++)
		{
			dTest[i] = numericalCopy[i][n - 1];
		}
		ThomasAlgorithm Ta(-a/2, 1, a/2, dTest, this->getVectorX().size());
		Ta.solve();
		for (int i = 0; i < this->getVectorX().size(); i++)
		{
			numericalCopy[i][n] = Ta.getX()[i];
		}
	}
	this->setNumerical(numericalCopy);
}

ImplicitFTCS::ImplicitFTCS() {} // this must be initialization list

ImplicitFTCS::ImplicitFTCS(double dT, double dx) : Scheme(dT, dx){}
