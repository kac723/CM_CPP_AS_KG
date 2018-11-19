#include "Implicit.h"
#include <fstream>
#include <ostream>
#include <iomanip>
#include <iterator>
#include <algorithm>

// Constructor
//Default constructor choose FTBS method, coefficients for thomas algorithm matrix are: -a, 1+a ,0
Implicit::Implicit() : method("FTBS"), TA(-(this->getA()), 1 + (this->getA()), 0.0, this->getVectorX().size())
{
	// Default constructor
}

//Constructor sets proper size of Thomas Algorithm matrix and depending on numerical method choosen 
//fills matrix for calculation for Thomas Algorithm with different coefficients.
//This constructor calls functios calculateNumericalSolution and calculateNorms.
Implicit::Implicit(string method, double dT, double dx) : Scheme(dT, dx), method(method)
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
	this->calculateNorms();
	this->printResults();
}

// Virtual Methods

//This function calculates numerical solution for implicit scheme.
//Calculations for implicit schemes are done by solving system of equations using Thomas Algorithm
//Coefficients matrix required for Thomas Algorithm is created in Implicit class constructor.
//Coefficients are set based on implicit method choosen - FTBS or FTCS
void Implicit::calculateNumericalSolution()
{
	// Variables
	// The function initializes variables with getter of the Scheme class. 
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

void Implicit::printResults()
{
	double timeMax = this->getTimeMax();
	double dT = (this->getVectorT()[1] - this->getVectorT()[0]);
	int timeVectorSize = this->getVectorT().size();
	int timePrintIndex[6] = { 0,0.1*(timeVectorSize / timeMax), 0.2*(timeVectorSize / timeMax), 0.3*(timeVectorSize / timeMax), 0.4*(timeVectorSize / timeMax), 0.5*(timeVectorSize / timeMax) };
	string dxS = to_string(short((this->getVectorX()[1] - this->getVectorX()[0])));
	string dxT = to_string(dT);
	dxT.erase(dxT.find_last_not_of('0') + 1);
	string fileName = "Implicit_" + method + "_" + "dx=" + dxS + "_" + "dt=" + dxT + ".txt";
	ofstream writeFile;
	writeFile.open(fileName);
	double norms[3] = { this->getNorms()[0],this->getNorms()[1],this->getNorms()[2] };
	writeFile << "Norms are:" << endl << "\t" << "-One norm: " << norms[0] << endl << "\t" << "-Two norm: " << norms[1] << endl << "\t" << "-Uniform norm: " << norms[2] << endl;
	writeFile <<"Numerical \t\t\t\t\t Analytical"<<endl<< "x " << "t=0s " << "t=0.1s " << "t=0.2s " << "t=0.3s " << "t=0.4s " << "t=0.5s" << endl;
	vector<double> xVector = this->getVectorX();
	int timePointer;
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
			writeFile << fixed << setprecision(6) << this->getAnalytical()[i][timePointer] ;
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