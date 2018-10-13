#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>

#define pi 4*atan(1) 

using namespace std;

// Test: Correct
void analyticalSolution(vector<vector<double>>& T, vector<double> xv, vector<double> tv)
{
	int x;
	int t;
	for (x = 0; x < T.size(); x++)
	{
		for (t = 0; t < T[0].size(); t++)
		{
			if (xv[x] < 50 + 250 * tv[t])
			{
				T[x][t] = 0;
			}

			else if ((xv[x] >= 50 + 250 * tv[t]) && (xv[x] < 110 + 250 * tv[t]))
			{
				T[x][t] = 100 * sin(pi*((xv[x] - 50) / (60)));
			}

			else if (xv[x] > 110 + 250 * tv[t])
			{
				T[x][t] = 0;
			}
		}
	}
}

// Test: Correct
void initialCondition(vector<vector<double>>& T, int sizeI, int sizeN)
{
	int i;
	int n;
	for (i = 0; i < sizeI; i++)
	{
		for (n = 0; n < sizeN; n++)
		{
			T[0][n] = 0;
		}
	}
}

// Test: Correct
void boundryCondition(vector<vector<double>>& T, int sizeI, int sizeN)
{
	int i;
	int n;

	for (i = 1; i < sizeI; i++)
	{
		for (n = 0 ; n < sizeN; n++)
		{
			T[sizeI - 1][n] = 0;
		}
	}
}

// Test: Only 0
void ExplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{
	int i;
	int n;
	for (i = 1; i < sizeI; i++)
	{
		for (n = 1; n < sizeN; n++)
		{
			T[i][n] = (1 - (deltaT / deltaX))*T[i][n - 1] + (deltaT / deltaX)*T[i - 1][n - 1];
		}
	}
}

// Test: No test
void ImplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{
	int i;
	int n;
	for (i = 1; i < sizeI; i++)
	{
		for (n = 1; n < sizeN; n++)
		{

		}
	}
}

// Test: Only 0
void LaxScheme(double deltaX, double deltaT, vector<vector<double>>& T, int sizeN, int sizeI)
{
	int i;
	int n;
	for (i = 1; i < sizeI - 1; i++)
	{
		for (n = 1; n < sizeN - 1; n++)
		{
			T[i][n] = 0.5*(T[i+1][n-1] + T[i - 1][n - 1]) - (deltaT / deltaX)*(T[i + 1][n - 1] - T[i - 1][n - 1]);
		}
	}
}

// Test: No test
void ImplicitSchemeFTCS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{

}

// Test: Correct
void print(vector<vector<double>>& T, ostream& out, vector<double>& V)
{
	int i;
	int n;
	for (i = 0; i < T.size(); i++)
	{
		out << fixed << setprecision(5) << V[i] << ", ";
		for (n = 0; n < T[0].size(); n++)
		{
			out << fixed << setprecision(5) << T[i][n];
			if (n != T[0].size() - 1)
				out << ", ";
		}
		out << endl;
	}
}

int main()
{
	cout << "#Hello world ! " << endl;

	// Declaration of variable	
	double deltaT = 0.1; // (For a better vue use 0.2)
	double deltaX = 5; // (For a better vue use 25)
	int L = 400;
	double timeMax = 1.0;

	// write value in an output file who we create
	ofstream file;
	file.open("output1.txt");

	
	ofstream analyticalFile;
	analyticalFile.open("analyticalOutput.txt");
	

	// definition of limit value
	int sizeSpace = (L / deltaX) + 1;
	int sizeTime = (timeMax / deltaT) + 1;

	// vecor with columns in space and raw in time (easier to plot it like that im gnuplot)	
	vector<vector<double>> T(sizeSpace, vector<double>(sizeTime));
	vector<vector<double>> TA(sizeSpace, vector<double>(sizeTime));

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
	cout << "T Size: " << T.size() << endl;
	cout << "T[0] Size: " << T[0].size() << endl;

	// use function
	analyticalSolution(TA, Vs, Vt);
	//ExplicitUpWindSchemeFTBS(T, sizeSpace, sizeTime, deltaX, deltaT);
	//LaxScheme(deltaX, deltaT,T,sizeTime,sizeSpace);
	
	// add condition 
	initialCondition(T, sizeSpace, sizeTime);
    boundryCondition(T, sizeSpace, sizeTime);

	// print in a txt file
	print(T, file, Vs);
	print(TA, analyticalFile, Vs);

	return 0;
}