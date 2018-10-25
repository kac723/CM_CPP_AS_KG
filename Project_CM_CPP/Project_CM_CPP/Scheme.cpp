#include "Scheme.h"
#include <cmath>

#define pi 4*atan(1.0)
using namespace std;

Scheme::Scheme(double dt, double dx)
{
	this->deltaT = dt;
	this->deltaX = dx;
	int sizeX = 1 + (this->L) / dx;
	int sizeT = 1 + (this->timeMax) / dt;
	this->AnalyticalResult=Matrix(sizeX, sizeT);
	this->initialCondition.resize(sizeX);
	this->leftBoundryCondition.resize(sizeT);
	this->rightBoundryCondition.resize(sizeT);
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
}

Scheme::Scheme()
{
	Scheme(1, 1);
}

void Scheme::initialAndBoundry()
{
	int n;
	for (n = 0; n < leftBoundryCondition.size(); n++)// we need to loop only in time (fill every point of time at points L and 0 - boundaries)
	{
		rightBoundryCondition[n] = 0;
		leftBoundryCondition[n] = 0; //boundry conditions are at x=L and x=0.
	}

	int i;
	for (i = 0; i < initialCondition.size(); i++)
	{
		if (xVector[i] < 50)
		{
			initialCondition[i] = 0;
		}
		else if ((xVector[i] >= 50) && (xVector[i] <= 110))
		{
			initialCondition[i] = 100 * sin(pi*((xVector[i] - 50) / 60));
		}
		else if (xVector[i] > 110)
		{
			initialCondition[i] = 0;
		}
	}
}

double Scheme::getU()
{
	return u;
}

vector<double>& Scheme::getVectorX()
{
	return xVector;
}

vector<double>& Scheme::getVectorT()
{
	return tVector;
}

std::vector<double>& Scheme::getInitial()
{
	return initialCondition;
}

std::vector<double>& Scheme::getLeftBoundry()
{
	return leftBoundryCondition;
}

std::vector<double>& Scheme::getRightBoundry()
{
	return rightBoundryCondition;
}

void Scheme::calculateAnalyticalResult()
{
	int x;
	int t;
	for (x = 0; x < xVector.size(); x++)
	{
		for (t = 0; t < tVector.size(); t++)
		{
			if (xVector[x] < (50 + 250 * tVector[t]))
			{
				AnalyticalResult[x][t] = 0;
			}

			else if ((xVector[x] >= (50 + 250 * tVector[t])) && (xVector[x] < (110 + 250 * tVector[t])))
			{
				AnalyticalResult[x][t] = 100 * sin(pi*((xVector[x] - 50 - 250 * tVector[t]) / (60))); //note: Axel, I think you forgot to write -250*tv[t] in equation here. now it looks better IMO. please check :), note2: I've just noticed that You used formula for initial condition here, I think this was the problem
			}

			else if (xVector[x] >= (110 + 250 * tVector[t]))
			{
				AnalyticalResult[x][t] = 0;
			}
		}
	}
}

Matrix& Scheme::getAnalytical()
{
	return AnalyticalResult;
}

Matrix & Scheme::getNumerical()
{
	return NumericalResult;
}

void Scheme::setNumerical(Matrix newNumerical)
{
	this->NumericalResult=Matrix(newNumerical);
}

double Scheme::getDeltaT()
{
	return deltaT;
}

double Scheme::getDeltaX()
{
	return deltaX;
}