#pragma once
#include "Scheme.h"
#include "ThomasAlgorithm.h"

class ImplicitFTCS :public Scheme, public ThomasAlgorithm
{
public:
	virtual void calculateNumericalSolution();
	ImplicitFTCS();
	ImplicitFTCS(double dT, double dx);
}; 
