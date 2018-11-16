#ifndef IMPLICIT_H //Include guard
#define IMPLICIT_H

#include "Scheme.h"
#include "ThomasAlgorithm.h"

using namespace std;

class Implicit :public Scheme
{
	private:
		string method;
		ThomasAlgorithm TA;
	public:
		virtual void calculateNumericalSolution();
		virtual void printResults();
		Implicit();
		Implicit(string method, double dT, double dx);
}; 


#endif