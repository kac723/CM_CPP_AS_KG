#include "ThomasAlgorithm.h"

//Default constructor
ThomasAlgorithm::ThomasAlgorithm()
{
	// Nothing
}

//Constructor assigns values passed as arguments: a, b, c to aCoef, bCoef, cCoef respectively.
//size value of Thomas Algorithm class will be initialized with newSize value
ThomasAlgorithm::ThomasAlgorithm(double a, double b, double c, int newSize): aCoef(a),bCoef(b),cCoef(c),size(newSize) 
{
	// Nothing
}

// Use for solve a tridiagonal systems of equations.
// This fntion uses the same variable of the lecture 4 page 20 of the computational method courses 
vector<double> ThomasAlgorithm::solve(vector<double> dVector)
{
	// Variables
	double m = 0;
	vector<double> aVector(this->size, this->aCoef);
	vector<double> bVector(this->size, this->bCoef);
	vector<double> cVector(this->size, this->cCoef);
	vector<double> xVector(this->size, 0);

	//Forward elimination phase
	for (int i = 1; i < this->size; i++)
	{
		m = aVector[i] / bVector[i - 1];
		bVector[i] = bVector[i] - (m * cVector[i - 1]);
		dVector[i] = dVector[i] - (m * dVector[i - 1]);
	}

	//Backward substitution phase
	//first we need to calculate first x value
	xVector[this->size - 1] = dVector[this->size - 1] / bVector[this->size - 1];

	for (int i = this->size - 2; i >= 0; i--)
	{
		xVector[i] = (dVector[i] - cVector[i] * xVector[i + 1]) / bVector[i];
	}

	return xVector;
}

// Setter functions 

//Function for setting a,b,c coefficients.
void ThomasAlgorithm::setCoefficients(double newA, double newB, double newC)
{
	this->aCoef = newA;
	this->bCoef = newB;
	this->cCoef = newC;
}

//Function for setting new size
void ThomasAlgorithm::setSize(int newSize)
{
	this->size = newSize;
}