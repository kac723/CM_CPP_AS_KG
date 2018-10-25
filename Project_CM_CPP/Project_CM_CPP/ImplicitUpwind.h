#pragma once
#include "Scheme.h"
#include "ThomasAlgorithm.h"

class ImplicitUpwind :public Scheme,public ThomasAlgorithm
{
	public:
		virtual void calculateNumericalSolution();
		ImplicitUpwind();
		ImplicitUpwind(double dT, double dx);
};