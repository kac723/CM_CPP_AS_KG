#include "Scheme.h"
#include <iomanip>
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

void Scheme::printResults(std::string schemeMethod)
{
	// Variables
	int timeVectorSize = tVector.size();
	int timePrintIndex[6] = { 0,0.1*(timeVectorSize / timeMax), 0.2*(timeVectorSize / timeMax), 0.3*(timeVectorSize / timeMax), 0.4*(timeVectorSize / timeMax), 0.5*(timeVectorSize / timeMax) };
	string dtS = to_string(deltaT);
	
	dtS.erase(dtS.find_last_not_of('0') + 1);
	
	// Creating the file and the name of the file
	string fileName = schemeMethod + "" + "dx=" + to_string(short(deltaX)) + "" + "dt=" + dtS + ".txt";
	ofstream writeFile;
	writeFile.open(fileName);
	
	// Adding the norm
	writeFile << "Norms are:" << endl << "\t" << "-One norm: " << norms[0] << endl << "\t" << "-Two norm: " << norms[1] << endl << "\t" << "-Uniform norm: " << norms[2] << endl;
	writeFile << "Numerical \t\t\t\t\t Analytical" << endl << "x " << "t=0s " << "t=0.1s " << "t=0.2s " << "t=0.3s " << "t=0.4s " << "t=0.5s" << endl;
	
	// Printing in the file fileName
	for (int i = 0; i < xVector.size(); i++)
	{
		writeFile << fixed << setprecision(6) << xVector[i] << ", ";
		for (int n = 0; n < 6; n++)
		{
			writeFile << fixed << setprecision(6) << NumericalResult[i][timePrintIndex[n]] << ", ";
		}

		for (int n = 0; n < 6; n++)
		{
			writeFile << fixed << setprecision(6) << AnalyticalResult[i][timePrintIndex[n]];
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

//Getter function

vector<double>& Scheme::getVectorX()
{
	return xVector;
}

vector<double>& Scheme::getVectorT()
{
	return tVector;
}

Matrix& Scheme::getNumerical()
{
	return NumericalResult;
}

double Scheme::getA()
{
	return u * deltaT / deltaX;
}


