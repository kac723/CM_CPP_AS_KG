#include "Explicit.h"
#include <fstream>
#include <ostream>
#include <iomanip>
#include <iterator>
#include <algorithm>

using namespace std;

double FTBS(double a, Matrix& numerical, int i, int n)
{
	return (1 - (a))*numerical[i][n - 1] + (a)*numerical[i - 1][n - 1];
}

double LW(double a, Matrix& numerical, int i, int n)
{
	//return (0.5*(numerical[i + 1][n - 1] + numerical[i - 1][n - 1]) - a*(numerical[i + 1][n - 1] - numerical[i - 1][n - 1]));
	//return ((numerical[i][n - 1]) - a * 0.5*(numerical[i + 1][n - 1] - numerical[i - 1][n - 1]));
	return numerical[i][n - 1] - 0.5*a*(numerical[i + 1][n - 1] - numerical[i - 1][n - 1]) +  (a*a*0.5)*(numerical[i + 1][n - 1] - 2*numerical[i][n - 1] + numerical[i - 1][n - 1]);
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
	for (int n = 1; n < vectorTSize; n++)
	{
		for (int i = 1; i < vectorXSize; i++)
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
	this->calculateNorms();
	this->printResults();
}

void Explicit::printResults()
{
	double timeMax = this->getTimeMax();
	double dT = (this->getVectorT()[1] - this->getVectorT()[0]);
	int timeVectorSize = this->getVectorT().size();
	int timePrintIndex[6] = { 0,0.1*(timeVectorSize /timeMax), 0.2*(timeVectorSize / timeMax), 0.3*(timeVectorSize / timeMax), 0.4*(timeVectorSize / timeMax), 0.5*(timeVectorSize / timeMax)};
	string dxS = to_string(short((this->getVectorX()[1]- this->getVectorX()[0])));
	string dxT = to_string(dT);
	dxT.erase(dxT.find_last_not_of('0') + 1);
	string fileName = "Explicit_" + method + "_" + "dx=" + dxS + "_" + "dt=" + dxT+".txt";
	ofstream writeFile;
	writeFile.open(fileName);
	double norms[3] = { this->getNorms()[0],this->getNorms()[1],this->getNorms()[2] };
	writeFile << "Norms are:" << endl << "\t" << "-One norm: " << norms[0] << endl << "\t" << "-Two norm: " << norms[1] << endl << "\t" << "-Uniform norm: " << norms[2] << endl;
	writeFile << "Numerical \t\t\t\t\t Analytical" << endl << "x " << "t=0s " << "t=0.1s " << "t=0.2s " << "t=0.3s " << "t=0.4s " << "t=0.5s" << endl;
	vector<double> xVector = this->getVectorX();
	int timePointer;
	for (int i = 0; i < xVector.size(); i++)
	{
		writeFile << fixed << setprecision(6) << xVector[i] << ", ";
		for (int n = 0; n < 6; n++)
		{
			timePointer = timePrintIndex[n];
			writeFile << fixed << setprecision(6) << this->getNumerical()[i][timePointer]<<", ";
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
}