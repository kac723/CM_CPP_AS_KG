#include "Scheme.h"
#include <cmath>

#define pi 4*atan(1.0)

// Constructor

Scheme::Scheme() 
{
	//Default constructor
}

Scheme::Scheme(double dt, double dx)
{
	// Initialization of the value of deltaT and deltaX
	this->deltaT = dt;
	this->deltaX = dx;

	// Create variables in order to create Matrix 
	int sizeX = 1 + (this->L) / dx;
	int sizeT = 1 + (this->timeMax) / dt;

	// Associate Matrix of the header with the size of we need
	this->AnalyticalResult=Matrix(sizeX, sizeT);
	this->NumericalResult=Matrix(sizeX, sizeT);

	// Space vector is filled with values from 0 to L (400) with step deltaX
	this->xVector.resize(sizeX);
	// Time vector is filled with values from 0 to timeMax (0.6) with step deltaT
	this->tVector.resize(sizeT);

	// Create all variables of the axis 
	for (int i = 1; i < sizeX; i++)
	{
		this->xVector[i] = this->xVector[i-1] + dx;
	}
	for (int n = 1; n < sizeT; n++)
	{
		this->tVector[n] = this->tVector[n - 1] + dt;
	}

	// We add the analytical result of the function 
	this->calculateAnalyticalResult();

	// After that we add the boudry because boudry condition have the priority
	this->initialAndBoundry();
}

// Function

void Scheme::initialAndBoundry()
{
	// Variables for the size of each vector
	int vectorXSize = xVector.size();
	int vectorTSize = tVector.size();

	// Boundry condition based on equation from the task description
	for (int n = 0; n < vectorTSize; n++)
	{

		this->NumericalResult[0][n] = 0;
		this->NumericalResult[vectorXSize -1][n] = 0;
	}

	// Initial condition based on eqation from the task description
	for (int i = 0; i < vectorXSize; i++)
	{
		// 0 < x < 50 ==> x = 0
		if (xVector[i] < 50)
		{
			this->NumericalResult[i][0] = 0;
		}
		// 50 <= x <= 110 ==> 100 * sin(pi*((x - 50) / 60))
		else if ((xVector[i] >= 50) && (xVector[i] <= 110))
		{
			this->NumericalResult[i][0] = 100 * sin(pi*((xVector[i] - 50) / 60));
		}
		// 110 <= x <= L ==> x = 0
		else if (xVector[i] > 110)
		{
			this->NumericalResult[i][0] = 0;
		}
	}
}

void Scheme::calculateAnalyticalResult()
{
	// Variables for the size of each vector
	int vectorXSize = xVector.size();
	int vectorTSize = tVector.size();

	// In order to fill all the value of the matrix AnalyticalResult
	for (int i = 0; i < vectorXSize; i++)
	{
		for (int n = 0; n < vectorTSize; n++)
		{
			// // 0 < x < 50 + 250*t ==> x = 0
			if (xVector[i] < (50 + 250 * tVector[n]))
			{
				AnalyticalResult[i][n] = 0;
			}
			// (50 + 250*t) <= x <= (110 + 250*t) ==> 100 * sin(pi*((x - 50 - 250*t) / 60))
			else if ((xVector[i] >= (50 + 250 * tVector[n])) && (xVector[i] < (110 + 250 * tVector[n])))
			{
				AnalyticalResult[i][n] = 100 * sin(pi*((xVector[i] - 50 - 250 * tVector[n]) / (60))); 
			}
			// (110 + 250*t) <= x <= L ==> x = 0
			else if (xVector[i] >= (110 + 250 * tVector[n]))
			{
				AnalyticalResult[i][n] = 0;
			}
		}
	}
}

void Scheme::calculateNorms()
{
	Matrix normMatrix(NumericalResult - AnalyticalResult);
	norms[0] = normMatrix.oneNorm();
	norms[1] = normMatrix.twoNorm();
	norms[2] = normMatrix.uniformNorm();
}

//Getter function

vector<double>& Scheme::getVectorX()
{
	return xVector;
}

vector<double>& Scheme::getVectorT()
{
	return tVector;
}

Matrix& Scheme::getAnalytical()
{
	return AnalyticalResult;
}

Matrix& Scheme::getNumerical()
{
	return NumericalResult;
}

double Scheme::getA()
{
	return u * deltaT / deltaX;
}


double* Scheme::getNorms()
{
	return this->norms;
}

double Scheme::getTimeMax()
{
	return this->timeMax;
}

