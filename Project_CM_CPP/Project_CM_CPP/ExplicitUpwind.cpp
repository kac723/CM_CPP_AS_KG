#include "ExplicitUpwind.h"


void ExplicitUpwind::calculateNumericalSolution()
{
	int i;
	int n;
	for (i = 1; i < this->getVectorX.size(); i++)
	{
		for (n = 1; n < this->getVectorT.size(); n++)
		{
			//T[i][n] = (1 - (((this->getU())*this->getDeltaT()) / this->getDeltaX()))*T[i][n - 1] + (((this->getU())*this->getDeltaT()) / this->getDeltaT())*T[i - 1][n - 1];
		}
	}
}

