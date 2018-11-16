#include "Explicit.h"
#include "Implicit.h"
#include "Matrix.h"
#include "Scheme.h"
#include "ThomasAlgorithm.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

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