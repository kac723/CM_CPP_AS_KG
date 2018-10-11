#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>

#define pi 4*atan(1) 
using namespace std;

void analyticalSolution(vector<vector<double>>& T, vector<double> xv, vector<double> tv)
{
	for (int t = 0; t < T[0].size(); t++)
	{
		for (int x = 0; x <= 50 + 250 * t; x++)
		{
			T[x][t] = 0;
		}

		for (int x = 50 + 250 * t; x < 110 + 250 * t; x++)
		{
			T[x][t] = 100 * sin(pi*((x - 50) / (60)));
		}

		for (int x = 110 + 250 * t; x < T.size(); x++)
		{
			T[x][t] = 0;
		}
	}
}

void initialCondition(vector<vector<double>>& T, int sizeI, int sizeN)
{
	for (int n = 1; n < sizeN; n++)
	{
		for (int i = 1; i < sizeI; i++)
		{
			T[0][n] = 0;
		}
	}
}
void boundryCondition(vector<vector<double>>& T, int sizeI, int sizeN)
{
	for (int n = 1; n < sizeN; n++)
	{
		for (int i = 1; i < sizeI; i++)
		{
			T[sizeI - 1][n] = 0;
		}
	}
}


void ExplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{
	for (int n = 1; n < sizeN; n++)
	{
		for (int i = 1; i < sizeI; i++)
		{
			T[i][n] = (1 - (deltaT / deltaX))*T[i][n - 1] + (deltaT / deltaX)*T[i - 1][n - 1];
		}
	}
}

void ImplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{
	for (int n = 1; n < sizeN; n++)
	{
		for (int i = 1; i < sizeI; i++)
		{

		}
	}
}

void LaxScheme(double deltaX, double deltaT, vector<vector<double>>& T, int sizeN, int sizeI)
{
	for (int n = 1; n < sizeN; n++)
	{
		for (int i = 1; i < sizeI - 1; i++)
		{
			T[n][i] = 0.5*(T[n - 1][i + 1] + T[n - 1][i - 1]) - (deltaT / deltaX)*(T[n - 1][i + 1] - T[n - 1][i - 1]);
		}
	}
}

void ImplicitSchemeFTCS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{

}

void print(vector<vector<double>>& T, ostream& out, vector<double>& V)
{
	for (int i = 0; i < T.size(); i++)
	{
		out << fixed << setprecision(5) << V[i] << ", ";
		for (int n = 0; n < T[0].size(); n++)
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
	double deltaT = 0.1;
	double deltaX = 5;
	int L = 400;
	double timeMax = 1.0;

	// write value in an output file who we create
	ofstream file;
	file.open("output.txt");

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

	// use function
	initialCondition(T, sizeSpace, sizeTime);
	boundryCondition(T, sizeSpace, sizeTime);
	analyticalSolution(TA, Vs, Vt);


	return 0;
}