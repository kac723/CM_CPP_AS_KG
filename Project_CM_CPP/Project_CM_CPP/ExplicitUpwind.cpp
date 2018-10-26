#include "ExplicitUpwind.h"


void ExplicitUpwind::calculateNumericalSolution()
{
	double a = this->getA();
	Matrix numericalCopy = this->getNumerical();
	for (int i = 1; i < this->getVectorX().size(); i++)
	{
		for( int n = 1; n < this->getVectorT().size(); n++)
		{
			numericalCopy[i][n] = (1 - (a))*numericalCopy[i][n - 1] + (a)*numericalCopy[i - 1][n - 1];
		}
	}
	this->setNumerical(numericalCopy);
}

ExplicitUpwind::ExplicitUpwind() {} // this must be initialization list

ExplicitUpwind::ExplicitUpwind(double dT, double dx) : Scheme(dT,dx)
{
	this->calculateNumericalSolution();
}
