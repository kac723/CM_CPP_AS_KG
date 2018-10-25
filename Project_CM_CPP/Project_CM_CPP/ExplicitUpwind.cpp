#include "ExplicitUpwind.h"


void ExplicitUpwind::calculateNumericalSolution()
{

	double dx = this->getDeltaX();
	double dt = this->getDeltaT();
	double u = this->getU();
	Matrix numericalCopy = this->getNumerical();
	for (int i = 1; i < this->getVectorX().size(); i++)
	{
		for( int n = 1; n < this->getVectorT().size(); n++)
		{
			numericalCopy[i][n] = (1 - ((u*dt) / dx))*numericalCopy[i][n - 1] + ((u*dt) / dx)*numericalCopy[i - 1][n - 1];
		}
	}
	this->setNumerical(numericalCopy);
}

ExplicitUpwind::ExplicitUpwind():Scheme(0.1,10) {} // this must be initialization list

ExplicitUpwind::ExplicitUpwind(double dT, double dx) : Scheme(dT,dx) {}
