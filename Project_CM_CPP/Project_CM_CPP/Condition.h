#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;

#define pi 4*atan(1) 

class Condition 
{
private:
public:
	Condition(); // default constructor
	void analyticalSolution(vector<vector<double>>& T, vector<double> xv, vector<double> tv);
	void initialCondition(vector<vector<double>>& T, vector<double> xv, int sizeI, int sizeN);
	void boudryCondition(vector<vector<double>>& T, int sizeI, int sizeN);
};Condition::Condition(){}void Condition::analyticalSolution(vector<vector<double>>& T, vector<double> xv, vector<double> tv){	int x;
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
				T[x][t] = 100 * sin(pi*((xv[x] - 50 - 250 * tv[t]) / (60))); //note: Axel, I think you forgot to write -250*tv[t] in equation here. now it looks better IMO. please check :), note2: I've just noticed that You used formula for initial condition here, I think this was the problem
			}

			else if (xv[x] >= (110 + 250 * tv[t]))
			{
				T[x][t] = 0;
			}
		}
	}}void Condition::initialCondition(vector<vector<double>>& T, vector<double> xv, int sizeI, int sizeN){	int i;
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
	}}
void Condition::boudryCondition(vector<vector<double>>& T, int sizeI, int sizeN)
{
	int n;
	for (n = 0; n < sizeN; n++)// we need to loop only in time (fill every point of time at points L and 0 - boundaries)
	{
		//boundry conditions are at x=L and x=0.
		T[sizeI - 1][n] = 0;
		T[0][n] = 0;
	}
}
