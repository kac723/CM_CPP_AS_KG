#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
#include "Matrix.h"
#include "ThomasAlgorithm.h"
#include "Scheme.h"
#include "Explicit.h"
#include "Implicit.h"
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

#define pi 4*atan(1) 

using namespace std;


void print(Matrix T, ostream& out, vector<double>& V)
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
	out << endl;
}


int main()
{
	double deltaX = 20;
	double deltaT = 0.1;
	//double deltaT[3] = { 0.02,0.01,0.005 };

	//Scheme* aP[12];

	//for (int i = 0; i < 3; i++)
	//{
	//	aP[i] = new ExplicitUpwind(deltaT[i], deltaX);
	//	aP[i+3] = new ExplicitLax(deltaT[i], deltaX);
	//	aP[i+6] = new ImplicitUpwind(deltaT[i], deltaX);
	//	//aP[i+9] = new ImplicitFTCS(deltaT[i], deltaX);
	//}
	//
	Scheme *s = new Explicit("FTBS", deltaT, deltaX);

	s->printResults();

	return 0;
}