#include "Explicit.h"
#include <fstream>
#include <ostream>
#include <iomanip>
#include <iterator>
#include <algorithm>


// Function for this class in order to find the method

// Function for the Forward derivation in time and bacward driavation in space (FTBS)
/**
Function created for return the value of the FTBS.
FTBS is Forward derivation in time and bacward driavation in space
Intialize this function with :
* coef in front of the second partial derivative (Type double)
* Function that we want to evaluate (Type Matrix)
* Space coefficient (Type int)
* Time coefficient (Type int)
* @return the value of the FTBS
*/
double FTBS(double a, Matrix& numerical, int i, int n)
{
	return (1 - (a))*numerical[i][n - 1] + (a)*numerical[i - 1][n - 1];
}

// Function for the Lax-Wendroff (LW) method 
/**
Function created for return the value of the LW.
LW is for the Lax-Wendroff method.
Intialize this function with :
* coef in front of the second partial derivative (Type double)
* Function that we want to evaluate (Type Matrix)
* Space coefficient (Type int)
* Time coefficient (Type int)
* @return the value of the LW
*/
double LW(double a, Matrix& numerical, int i, int n)
{
	return numerical[i][n - 1] - 0.5*a*(numerical[i + 1][n - 1] - numerical[i - 1][n - 1]) + (a*a*0.5)*(numerical[i + 1][n - 1] - 2 * numerical[i][n - 1] + numerical[i - 1][n - 1]);
}

// Constructor
/**
By default, the calculation method is FTBS -> Upwind
*/
Explicit::Explicit() :method("FTBS")
{
	// Nothing
}

//Constructor defines value of functionPtr. 
//This is variable that points to function and will point to function FTBS or LW.
//Those functions calculated numerical result based on proper equation evaluated for each method.
Explicit::Explicit(string newMethod, double dT, double dx) : Scheme(dT, dx), method(newMethod)
{
	if (method == "FTBS")
	{
		functionPtr = FTBS;
	}
	else if (method == "LW")
	{
		functionPtr = LW;
	}
	// calls functios calculateNumericalSolution and calculateNorms.
	this->calculateNumericalSolution();
	this->calculateNorms();
	//Then we print the result with the function printResult
	this->printResults("Explicit_" + method);
}

// Method

void Explicit::modifyCaluclationLimits(int &spaceLimit, int &timeLimit)
{
	// For Lax-Wendroff method we need to modify limits of calculation for space.
	if (method == "LW")
	{
		// It's caused by Lax-Wendroff equation indexes so the function modificates it.
		spaceLimit--;
	}
}

// Virtual Methods

void Explicit::calculateNumericalSolution()
{
	// Variables
	// The function initializes variables with getter of the Scheme class.
	double a = this->getA();
	int vectorXSize = this->getVectorX().size();
	int vectorTSize = this->getVectorT().size();

	//The function modificates the value if we use the LW function 
	modifyCaluclationLimits(vectorXSize, vectorTSize);

	// Then, the function calculates the numerical result
	for (int n = 1; n < vectorTSize; n++)
	{
		for (int i = 1; i < vectorXSize; i++)
		{
			this->getNumerical()[i][n] = functionPtr(a, this->getNumerical(), i, n);
		}
	}
}
