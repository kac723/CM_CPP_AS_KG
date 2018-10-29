#include "Implicit.h"
#include <iterator>
using namespace std;

//This function calculates numerical solution for implicit scheme.
//Calculations for implicit schemes are done by solving system of equations using Thomas Algorithm
//Coefficients matrix required for Thomas Algorithm is created in Implicit class constructor.
//Coefficients are set based on implicit method choosen - FTBS or FTCS
void Implicit::calculateNumericalSolution()
{
	int vectorXSize = this->getVectorX().size();
	int vectorTSize = this->getVectorT().size();
	vector<double> dVector(vectorXSize);
	vector<double> resultVector(vectorXSize, 0);
	for (int n = 1; n < vectorTSize; n++)
	{
		for (int i = 0; i < vectorXSize; i++)
		{
			dVector[i] = this->getNumerical()[i][n - 1];
		}
		resultVector=TA.solve(dVector);
		for (int i = 0; i < vectorXSize; i++)
		{
			this->getNumerical()[i][n] = resultVector[i];
		}
	}
}
//Default constructor choose FTBS method, coefficients for thomas algorithm matrix are: -a, 1+a ,0
Implicit::Implicit() : method("FTBS"),TA(-(this->getA()),1+ (this->getA()) ,0.0,this->getVectorX().size()){} 

//Constructor sets proper size of Thomas Algorithm matrix and depending on numerical method choosen 
//fills matrix for calculation for Thomas Algorithm with different coefficients.
//This constructor calls functios calculateNumericalSolution and calculateNorms.
Implicit::Implicit(string method,double dT, double dx) : Scheme(dT, dx),method(method)
{
	TA.setSize(this->getVectorX().size());
	double a = this->getA();
	if (method == "FTCS")
	{
		this->TA.setCoefficients(-a / 2, 1, a / 2); 
	}
	else if (method == "FTBS")
	{
		this->TA.setCoefficients(-a, 1 + a, 0);
	}

	this->calculateNumericalSolution();
	//this->calculateNorms();
}


