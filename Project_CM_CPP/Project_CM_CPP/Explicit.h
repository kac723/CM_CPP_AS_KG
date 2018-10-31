#pragma once
#include "Scheme.h"

class Explicit: public Scheme
{	
	private:
		std::string method;
		double (*functionPtr)(double, Matrix&,int,int);
	public:
		virtual void calculateNumericalSolution() ;
		virtual void printResults();
		Explicit();
		Explicit(std::string newMethod,double dT, double dx);
		void modifyCaluclationLimits(int &spaceLimit, int &timeLimit);
};