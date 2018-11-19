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
	this->printResults();
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


void Explicit::printResults()
{
	// Variables
	// Initializing variables with getter of the Scheme class.
	double timeMax = this->getTimeMax();
	double dT = (this->getVectorT()[1] - this->getVectorT()[0]);
	int timeVectorSize = this->getVectorT().size();

	int timePrintIndex[6] = { 0,0.1*(timeVectorSize / timeMax), 0.2*(timeVectorSize / timeMax), 0.3*(timeVectorSize / timeMax), 0.4*(timeVectorSize / timeMax), 0.5*(timeVectorSize / timeMax) };
	string dxS = to_string(short((this->getVectorX()[1] - this->getVectorX()[0])));
	string dxT = to_string(dT);
	dxT.erase(dxT.find_last_not_of('0') + 1);

	// Creating the file and the name of the file
	string fileName = "Explicit_" + method + "_" + "dx=" + dxS + "_" + "dt=" + dxT + ".txt";
	ofstream writeFile;
	writeFile.open(fileName);

	// Adding the norm of the Scheme class
	double norms[3] = { this->getNorms()[0],this->getNorms()[1],this->getNorms()[2] };
	
	// Write in the file
	writeFile << "Norms are:" << endl << "\t" << "-One norm: " << norms[0] << endl << "\t" << "-Two norm: " << norms[1] << endl << "\t" << "-Uniform norm: " << norms[2] << endl;
	writeFile << "Numerical \t\t\t\t\t Analytical" << endl << "x " << "t=0s " << "t=0.1s " << "t=0.2s " << "t=0.3s " << "t=0.4s " << "t=0.5s" << endl;
	
	vector<double> xVector = this->getVectorX();
	int timePointer;

	// Printing in the file fileName
	for (int i = 0; i < xVector.size(); i++)
	{
		writeFile << fixed << setprecision(6) << xVector[i] << ", ";
		for (int n = 0; n < 6; n++)
		{
			timePointer = timePrintIndex[n];
			writeFile << fixed << setprecision(6) << this->getNumerical()[i][timePointer] << ", ";
		}

		for (int n = 0; n < 6; n++)
		{
			timePointer = timePrintIndex[n];
			writeFile << fixed << setprecision(6) << this->getAnalytical()[i][timePointer];
			if (n != this->getVectorT().size() - 1)
			{
				writeFile << ", ";
			}
		}

		writeFile << endl;
	}
	writeFile.close();
	cout << "The file " << fileName << " as been created in the project folder" << endl;
}



