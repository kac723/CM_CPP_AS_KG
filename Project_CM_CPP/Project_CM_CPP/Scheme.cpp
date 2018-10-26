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
	this->NumericalResult=Matrix(sizeX, sizeT);
	this->norms.resize(3);
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

Scheme::Scheme() {}

void Scheme::initialAndBoundry()
{
	int n;
	for (n = 0; n < this->getVectorT().size(); n++)// we need to loop only in time (fill every point of time at points L and 0 - boundaries)
	{

		this->NumericalResult[0][n] = 0;
		this->NumericalResult[this->getVectorX().size()-1][n] = 0;
	}

	int i;
	for (i = 0; i < this->getVectorX().size(); i++)
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

vector<double>& Scheme::getVectorX()
{
	return xVector;
}

vector<double>& Scheme::getVectorT()
{
	return tVector;
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

double Scheme::getA()
{
	return u * deltaT / deltaX;
}

void Scheme::calculateNorms()
{
	Matrix normMatrix((this->getNumerical()-this->getAnalytical()));
	norms[0] = normMatrix.oneNorm();
	norms[1] = normMatrix.twoNorm();
	norms[2] = normMatrix.uniformNorm();
}