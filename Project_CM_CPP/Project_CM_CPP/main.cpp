#include <iostream>
#include "Matrix.h"
#include "ThomasAlgorithm.h"
#include "Scheme.h"
#include "Explicit.h"
#include "Implicit.h" 

using namespace std;

int main()
{
	double deltaX = 5;
	double deltaT[3] = { 0.02,0.01,0.005 };

	Scheme* aP[12];

	for (int i = 0; i < 3; i++)
	{
		aP[i] = new Explicit("FTBS",deltaT[i], deltaX);
		aP[i+3] = new Explicit("LW",deltaT[i], deltaX);

		aP[i+6] = new Implicit("FTBS", deltaT[i], deltaX);
		aP[i+9] = new Implicit("FTCS",deltaT[i], deltaX);
	}


	return 0;
}