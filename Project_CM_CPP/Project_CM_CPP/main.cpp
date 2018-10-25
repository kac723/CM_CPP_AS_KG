#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
#include "Matrix.h"
#include "ThomasAlgorithm.h"
#include "Scheme.h"
#include "ExplicitUpwind.h"

#define pi 4*atan(1) 

using namespace std;

// Test: Correct
void analyticalSolution(Matrix& T, vector<double> xv, vector<double> tv)
{
	int x;
	int t;
	for (x = 0; x < T.getCols(); x++)
	{
		for (t = 0; t < T.getRows(); t++)
		{
			if (xv[x] < (50 + 250 * tv[t]))
			{
				T[x][t] = 0;
			}

			else if ((xv[x] >= (50 + 250 * tv[t])) && (xv[x] < (110 + 250 * tv[t])))
			{
				T[x][t] = 100 * sin(pi*((xv[x] - 50-250*tv[t]) / (60))); //note: Axel, I think you forgot to write -250*tv[t] in equation here. now it looks better IMO. please check :), note2: I've just noticed that You used formula for initial condition here, I think this was the problem
			}

			else if (xv[x] >= ( 110 + 250 * tv[t]))
			{
				T[x][t] = 0;
			}
		}
	}
}

// Test: Correct
//14/10: inital condition was incorrect. its sin(..). 0 is for boundry condition
void initialCondition(Matrix& T, vector<double> xv, int sizeI, int sizeN)
{
	int i;
	for (i = 0; i < sizeI; i++)
	{
		if (xv[i] < 50)
		{
			T[i][0] = 0;
		}
		else if ((xv[i] >= 50) && (xv[i] <= 110))
		{
			T[i][0] = 100 * sin(pi*((xv[i] - 50) / 60));
		}
		else if (xv[i] > 110)
		{
			T[i][0] = 0;
		}
	}
}

// Test: Correct
void boundryCondition(Matrix& T, int sizeI, int sizeN)
{
	int n;
		for (n = 0 ; n < sizeN; n++)// we need to loop only in time (fill every point of time at points L and 0 - boundaries)
		{
			T[sizeI - 1][n] = 0;
			T[0][n] = 0; //boundry conditions are at x=L and x=0.
		}
}

// Test: Correct. Norms tests required for further analysis
//14/10 we had error in equation (missing u parameter).
void ExplicitUpWindSchemeFTBS(Matrix& T, int sizeI, int sizeN, double deltaX, double deltaT, double u)
{
	int i;
	int n;
	for (i = 1; i < sizeI; i++)
	{
		for (n = 1; n < sizeN; n++)
		{
			T[i][n] = (1 - ((u*deltaT) / deltaX))*T[i][n - 1] + ((u*deltaT) / deltaX)*T[i - 1][n - 1];
		}
	}
}

// Test: Correct. Norms tests required for further analysis
//14/10 we had error in equation (missing u parameter).
void LaxScheme(double deltaX, double deltaT, Matrix& T, int sizeN, int sizeI, double u)
{
	int i;
	int n;
	for (i = 1; i < sizeI - 1; i++)
	{
		for (n = 1; n < sizeN - 1; n++)
		{
			T[i][n] = 0.5*(T[i+1][n-1] + T[i - 1][n - 1]) - ((u*deltaT) / deltaX)*(T[i + 1][n - 1] - T[i - 1][n - 1]);
		}
	}
}

void SubstractTables(vector<vector<double>>& T1, vector<vector<double>>& T2, vector<vector<double>>& TResult, int sizeI, int sizeN)
{
	for (int i = 0; i < sizeI; i++)
	{
		for (int n = 0; n < sizeN; n++)
		{
			TResult [i][n] = T2[i][n] - T1[i][n];
		}
	}
}
// Test: Correct
void print(Matrix& T, ostream& out, vector<double>& V)
{
	int i;
	int n;
	for (i = 0; i < T.getCols(); i++)
	{
		out << fixed << setprecision(5) << V[i] << ", ";
		for (n = 0; n < T.getRows(); n++)
		{
			out << fixed << setprecision(5) << T[i][n];
			if (n != T[0].size() - 1)
				out << ", ";
		}
		out << endl;
	}
}
//Test: Correct
void ThomasAlgorithmFunc(vector<double> a, vector<double> b, vector<double> c, vector<double>& x, vector<double> d, int sizeI)
{
	double m = 0;
	double newD, newB;
	//Forward elimination phase
	for (int i = 1; i < sizeI; i++)
	{
		m = a[i] / b[i - 1];
		b[i] = b[i] - (m * c[i - 1]);
		d[i] = d[i] - (m * d[i - 1]);
	}
	//Backward substitution phase
	//first we need to calculate first x value
	x[sizeI - 1] = d[sizeI - 1] / b[sizeI - 1];
	for (int i = sizeI - 2; i >= 0; i--)
	{
		x[i] = (d[i] - c[i] * x[i + 1]) / b[i];
	}
}

// Test: In progress. Plots make sense, but when time increases accuracy of result dicrese significantly. This is beta version. Requires better coding style
void ImplicitUpWindSchemeFTBS(Matrix& T, int sizeI, int sizeN, double deltaX, double deltaT, double a)
{
	vector<double> dTest(sizeI);
	for (int n = 1; n < sizeN; n++)
	{
		for (int i = 0; i < sizeI; i++)
		{
			dTest[i] = T[i][n - 1];
		}
		ThomasAlgorithm Ta(-a, 1 + a, 0, dTest, sizeI);
		Ta.solve();
		for (int i = 0; i < sizeI; i++)
		{
			T[i][n] = Ta.getX()[i];
		}
	}

}

// Test: In progress. Makes sense but only for very small deltaT .e.g 0.001. I will look further into it
void ImplicitSchemeFTCS(Matrix& T, int sizeI, int sizeN, double deltaX, double deltaT, double a)
{
	vector<double> aTest(sizeI, -a/2);
	vector<double> bTest(sizeI, 1); //this creates vector of sizeSpace values. all equal to 1+a
	vector<double> cTest(sizeI, a/2);
	vector<double> dTest(sizeI);
	vector<double> zeros(sizeI, 0);
	vector<double> xVector(sizeI, 0);
	for (int n = 1; n < sizeN; n++)
	{
		for (int i = 0; i < sizeI; i++)
		{
			dTest[i] = T[i][n - 1];
		}
		ThomasAlgorithmFunc(aTest, bTest, cTest, xVector, dTest, sizeI); //I think we should operate in space dimension from 1st element to Ith-1. not from 0th to nth. I need to verify that
		for (int i = 0; i < sizeI; i++)
		{
			T[i][n] = xVector[i];
		}
		xVector = zeros;
	}

}
int main()
{
	// Declaration of variable	
	double deltaT = 0.1; // (For a better view use 0.2) REMEMBER: u*deltaT/deltaX must be less then 1 for explicit schemes
	double deltaX = 30; // (For a better view use 25)
	int L = 400;
	double timeMax = 0.6;
	double u = 250.0;
	double a = u * (deltaT / deltaX);


	// write value in an output file who we create
	ofstream file;
	file.open("output.txt");

	
	ofstream analyticalFile;
	analyticalFile.open("analyticalOutput.txt");
	

	// definition of limit value
	int sizeSpace = (L / deltaX) + 1;
	int sizeTime = (timeMax / deltaT) + 1;

	Matrix mTest(sizeSpace, sizeTime);
	Matrix mTestAna(sizeSpace, sizeTime);

	vector<double> Vs(sizeSpace);
	vector<double> Vt(sizeTime);

	for (int i = 1; i < Vs.size(); i++)
	{
		Vs[i] = Vs[i - 1] + deltaX;
	}

	for (int n = 1; n < Vt.size(); n++)
	{
		Vt[n] = Vt[n - 1] + deltaT;
	}

	cout << "Space Size: " << Vs.size() << endl;
	cout << "Time Size: " << Vt.size() << endl;  
	cout << "T Size: " << mTest.getCols() << endl;
	cout << "T[0] Size: " << mTest.getRows() << endl;

	// add condition 
	initialCondition(mTest, Vs, sizeSpace, sizeTime);
	boundryCondition(mTest, sizeSpace, sizeTime);

	// use function
	analyticalSolution(mTestAna, Vs, Vt);
	ExplicitUpWindSchemeFTBS(mTest, sizeSpace, sizeTime, deltaX, deltaT,u);
	//LaxScheme(deltaX, deltaT,mTest,sizeTime,sizeSpace,u); // Lax Scheme is unstable always so we won't get good results. (as can be seen on plots)
	//ImplicitUpWindSchemeFTBS(mTest, sizeSpace, sizeTime, deltaX, deltaT, a);
	//ImplicitSchemeFTCS(mTest, sizeSpace, sizeTime, deltaX, deltaT, a);

	// print in a txt file
	print(mTest, cout, Vs);
	//print(mTestAna, cout, Vs);
	
	ExplicitUpwind explicitTest(0.1, 30);
	Scheme* aP=new ExplicitUpwind(0.1,30);
	explicitTest.initialAndBoundry();
	print(explicitTest.getNumerical(), cout, Vs);

	explicitTest.calculateNumericalSolution();
	
	print(explicitTest.getNumerical(), cout, Vs);

	Matrix norms(mTest-mTestAna);
	print(norms, cout, Vs);
	cout << norms.oneNorm()<<endl;
	cout << norms.twoNorm() << endl;
	cout << norms.uniformNorm() << endl;
	analyticalFile.close();
	file.close();
	return 0;
}