#include "Scheme.h"
#include <cmath>

#define pi 4*atan(1.0)
using namespace std;

//Default constructor
Scheme::Scheme() {}


//Constructor allocates required size for vectors and matrixes based on assigned deltaT and deltaX values
//Space and Time vector are filled with values from 0 to L(400) with step deltaX for space vector 
//and from 0 to timeMax(0.6) with step deltaT for time vector.
//Based on created vectors analytical result is calculated and initial and boundry conditions are applied for further calculations
//for numerical method
Scheme::Scheme(double dt, double dx)
{
	this->deltaT = dt;
	this->deltaX = dx;
	int sizeX = 1 + (this->L) / dx;
	int sizeT = 1 + (this->timeMax) / dt;
	this->AnalyticalResult=Matrix(sizeX, sizeT);
	this->NumericalResult=Matrix(sizeX, sizeT);
	this->xVector.resize(sizeX);
	this->tVector.resize(sizeT);
	for (int i = 1; i < sizeX; i++)
	{
		this->xVector[i] = this->xVector[i-1] + dx;
	}

	for (int n = 1; n < sizeT; n++)
	{
		this->tVector[n] = this->tVector[n - 1] + dt;
	}
	this->calculateAnalyticalResult();
	this->initialAndBoundry();
}

//applying boundry condition and then initial condition based on equation from task description.
void Scheme::initialAndBoundry()
{
	int vectorXSize = xVector.size();
	int vectorTSize = tVector.size();
	for (int n = 0; n < vectorTSize; n++)
	{

		this->NumericalResult[0][n] = 0;
		this->NumericalResult[vectorXSize -1][n] = 0;
	}

	for (int i = 0; i < vectorXSize; i++)
	{
		if (xVector[i] < 50)
		{
			this->NumericalResult[i][0] = 0;
		}
		else if ((xVector[i] >= 50) && (xVector[i] <= 110))
		{
			this->NumericalResult[i][0] = 100 * sin(pi*((xVector[i] - 50) / 60));
		}
		else if (xVector[i] > 110)
		{
			this->NumericalResult[i][0] = 0;
		}
	}
}

//Getter function for space vector. Returns vector<double> xVector.
vector<double>& Scheme::getVectorX()
{
	return xVector;
}
//Getter function for time vector. Returns vector<double> tVector.
vector<double>& Scheme::getVectorT()
{
	return tVector;
}

//Function calculates analytical result based on equation from task description and stores results in AnalyticalResult matrix
void Scheme::calculateAnalyticalResult()
{
	int vectorXSize = xVector.size();
	int vectorTSize = tVector.size();
	for (int i = 0; i < vectorXSize; i++)
	{
		for (int n = 0; n < vectorTSize; n++)
		{
			if (xVector[i] < (50 + 250 * tVector[n]))
			{
				AnalyticalResult[i][n] = 0;
			}

			else if ((xVector[i] >= (50 + 250 * tVector[n])) && (xVector[i] < (110 + 250 * tVector[n])))
			{
				AnalyticalResult[i][n] = 100 * sin(pi*((xVector[i] - 50 - 250 * tVector[n]) / (60))); 
			}

			else if (xVector[i] >= (110 + 250 * tVector[n]))
			{
				AnalyticalResult[i][n] = 0;
			}
		}
	}
}

//Getter function for analytical result. Returns Matrix AnalyticalResult
Matrix& Scheme::getAnalytical()
{
	return AnalyticalResult;
}

//Getter function for numerical result. Returns Matrix NumericalResult
Matrix & Scheme::getNumerical()
{
	return NumericalResult;
}

//Function returns A coefficient of wave equation: u*deltaT/deltaX. u is constant=250
double Scheme::getA()
{
	return u * deltaT / deltaX;
}

//Function calculates one norm, two norm and uniform norm and stores results in array norms
void Scheme::calculateNorms()
{
	Matrix normMatrix(NumericalResult-AnalyticalResult);
	norms[0] = normMatrix.oneNorm();
	norms[1] = normMatrix.twoNorm();
	norms[2] = normMatrix.uniformNorm();
}