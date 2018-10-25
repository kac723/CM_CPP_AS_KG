#include "ExplicitLax.h"


void ExplicitLax::calculateNumericalSolution()
{
	double a = this->getA();
	Matrix numericalCopy = this->getNumerical();
	for (int i = 1; i < this->getVectorX().size()-1; i++)
	{
		for (int n = 1; n < this->getVectorT().size()-1; n++)
		{
			numericalCopy[i][n] = 0.5*(numericalCopy[i + 1][n - 1] + numericalCopy[i - 1][n - 1]) - a*(numericalCopy[i + 1][n - 1] - numericalCopy[i - 1][n - 1]);
		}
	}
	this->setNumerical(numericalCopy);
}

ExplicitLax::ExplicitLax() {} // this must be initialization list

ExplicitLax::ExplicitLax(double dT, double dx) : Scheme(dT, dx) {}
