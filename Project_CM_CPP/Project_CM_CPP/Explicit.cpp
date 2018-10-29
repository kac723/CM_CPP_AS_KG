#include "Explicit.h"

using namespace std;

double FTBS(double a, Matrix& numerical, int i, int n)
{
	return (1 - (a))*numerical[i][n - 1] + (a)*numerical[i - 1][n - 1];
}

double LW(double a, Matrix& numerical, int i, int n)
{
	return 0.5*(numerical[i + 1][n - 1] + numerical[i - 1][n - 1]) - a * (numerical[i + 1][n - 1] - numerical[i - 1][n - 1]);
}

//calculating numerical result based on method specified in constructor (FTBS or LW)
//before starting calculation function modifyCaluclationLimits is called in order to modify limits of calculation. This is necessary opeartion 
//for Lax-Wendroff method. 
//function calculateNumericalSolution is virtual function from abstract class Scheme.
//As Explicit class inherit from Scheme it must implement this function.
void Explicit::calculateNumericalSolution()
{
	double a = this->getA();
	int vectorXSize = this->getVectorX().size();
	int vectorTSize = this->getVectorT().size();
	modifyCaluclationLimits(vectorXSize, vectorTSize);
	for (int i = 1; i < vectorXSize; i++)
	{
		for( int n = 1; n < vectorTSize; n++)
		{
			this->getNumerical()[i][n] = functionPtr(a, this->getNumerical(), i, n);
		}
	}
}

// function created for future purposes. When creating new methods it may be necessary to change space or time limits in different way
void Explicit::modifyCaluclationLimits(int &spaceLimit, int &timeLimit) 
{
	if (method == "LW")
	{
		spaceLimit--; // for Lax-Wendroff method we need to modify limits of calculation for space. It's caused by Lax-Wendroff equation indexes
	}
}

// default calculation method is FTBS -> Upwind
Explicit::Explicit():method("FTBS") {} 

//Constructor defines value of functionPtr. This is variable that points to function and will point to function FTBS or LW.
//Those functions calculated numerical result based on proper equation evaluated for each method.
//This constructor calls functios calculateNumericalSolution and calculateNorms.
Explicit::Explicit(string newMethod,double dT, double dx) : Scheme(dT,dx),method(newMethod)
{
	if (method == "FTBS")
	{
		functionPtr = FTBS;
	}
	else if (method == "LW")
	{
		functionPtr = LW;
	}
	this->calculateNumericalSolution();
	//this->calculateNorms();
}
