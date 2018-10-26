#include "ImplicitUpwind.h"

using namespace std;
void ImplicitUpwind::calculateNumericalSolution()
{
	Matrix numericalCopy = this->getNumerical();
	vector<double> dTest(this->getVectorX().size());
	double a = this->getA();
	ThomasAlgorithm TA(-a , 1+a, 0, this->getVectorX().size());
	vector<double> resultVector(this->getVectorX().size(), 0);
	for (int n = 1; n < this->getVectorT().size(); n++)
	{
		for (int i = 0; i < this->getVectorX().size(); i++)
		{
			dTest[i] = numericalCopy[i][n - 1];
		}
		resultVector = TA.solve(dTest);
		for (int i = 0; i < this->getVectorX().size(); i++) //maybe lambda expression
		{
			numericalCopy[i][n] = resultVector[i];
		}
	}
	this->setNumerical(numericalCopy);
}

ImplicitUpwind::ImplicitUpwind() {} 

ImplicitUpwind::ImplicitUpwind(double dT, double dx) : Scheme(dT, dx),ThomasAlgorithm() 
{
	this->calculateNumericalSolution();
}
