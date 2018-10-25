#pragma once

#include "Scheme.h"
class ExplicitUpwind: public Scheme
{	
	public:
		virtual void calculateNumericalSolution() ;
		ExplicitUpwind();
		ExplicitUpwind(double dT, double dx);
};