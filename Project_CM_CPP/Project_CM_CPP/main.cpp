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
void initialCondition(vector<vector<double>>& T, vector<double> xv, int sizeI, int sizeN)
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
void boundryCondition(vector<vector<double>>& T, int sizeI, int sizeN)
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
void ExplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT, double u)
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

// Test: Correct. Norms tests required for further analysis
//14/10 we had error in equation (missing u parameter).
void LaxScheme(double deltaX, double deltaT, vector<vector<double>>& T, int sizeN, int sizeI, double u)
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
double one_norm(vector<vector<double>>& T, int sizeI, int sizeN) //one norm is maximum of sum of columns
{
	double sum = 0;
	double NewResult = 0;
	double result = 0;
	for (int n = 0; n < sizeN; n++)
	{
		for (int i = 0; i < sizeI; i++)
		{
			sum += abs(T[i][n]); //summing values from one column in loop. 
		}
		NewResult = sum;
		sum = 0;
		if (NewResult > result) //if new result is bigger then previous then we update result value
		{
			result = NewResult;
		}

	}
	return result;
}
double uniform_norm(vector<vector<double>>& T, int sizeI, int sizeN) //one norm is maximum of sum of columns
{
	double sum = 0;
	double NewResult = 0;
	double result = 0;
	for (int i = 0; i < sizeI; i++)
	{
		for (int n = 0; n < sizeN; n++)
		{
			sum += abs(T[i][n]); //summing values from one row in loop. 
		}
		NewResult = sum;
		sum = 0;
		if (NewResult > result) //if new result is bigger then previous then we update result value
		{
			result = NewResult;
		}

	}
	return result;
}
double two_norm(vector<vector<double>>& T, int sizeI,int sizeN)
{
	double result=0;
	for (int i = 0; i < sizeI; i++)
	{
		for (int n = 0; n < sizeN; n++)
		{
			result += pow(abs(T[i][n]),2);
		}
	}
	return sqrt(result);
}
int main()
{
	cout << "#Hello world ! " << endl;

	// Declaration of variable	
	double deltaT = 0.2; // (For a better view use 0.2)
	double deltaX = 50; // (For a better view use 25)
	int L = 400;
	double timeMax = 1.0;
	double u = 250;

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
	vector<vector<double>> TC(sizeSpace, vector<double>(sizeTime)); // Table to Compare analytical result with numerical result

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

	// add condition 
	initialCondition(T, Vs, sizeSpace, sizeTime);
	boundryCondition(T, sizeSpace, sizeTime);

	// use function
	analyticalSolution(TA, Vs, Vt);
	ExplicitUpWindSchemeFTBS(T, sizeSpace, sizeTime, deltaX, deltaT,u);
	//LaxScheme(deltaX, deltaT,T,sizeTime,sizeSpace,u); // Lax Scheme is unstable always so we won't get good results. (as can be seen on plots)
	
	//compare of results using norms after calculation
	SubstractTables(TA, T, TC, sizeSpace, sizeTime);
	// print in a txt file
	print(T, cout, Vs);
	cout << endl;
	print(TA, cout, Vs);
	cout << endl;
	print(TC, cout, Vs);
	cout << "One norm is: " << one_norm(TC, sizeSpace, sizeTime)<<endl;
	cout << "Two norm is: " << two_norm(TC, sizeSpace, sizeTime)<<endl;
	cout << "Uniform norm is: " << uniform_norm(TC, sizeSpace, sizeTime) << endl;
	return 0;
}