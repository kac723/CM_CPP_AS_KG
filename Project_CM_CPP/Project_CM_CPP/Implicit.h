#pragma once
#include "Scheme.h"
#include "ThomasAlgorithm.h"

class Implicit :public Scheme
{
	private:
		std::string method;
		ThomasAlgorithm TA;
	public:
		virtual void calculateNumericalSolution();
		virtual void printResults();
		Implicit();
		Implicit(std::string method, double dT, double dx);
}; 
