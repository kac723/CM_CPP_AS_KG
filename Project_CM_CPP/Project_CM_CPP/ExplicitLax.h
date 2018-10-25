#pragma once

#include "Scheme.h"
class ExplicitLax : public Scheme
{
public:
	virtual void calculateNumericalSolution();
	ExplicitLax();
	ExplicitLax(double dT, double dx);
}; 
