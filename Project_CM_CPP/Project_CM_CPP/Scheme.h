#ifndef SCHEME_H //Include guard
#define SCHEME_H

#include <vector>
#include <ostream>
#include <string>
#include "Matrix.h"

using namespace std;

class Scheme
{
	private:
		double deltaT;
		double deltaX;
		const double u = 250;
		const int L = 400;
		const double timeMax = 0.6;
		vector<double> xVector;
		vector<double> tVector;
		Matrix NumericalResult;
		Matrix AnalyticalResult;
		double norms[3];
	public:
		Scheme();
		Scheme(double dt, double dx);
		void calculateAnalyticalResult();
		Matrix& getAnalytical();
		double getA();
		Matrix& getNumerical();
		void initialAndBoundry();
		vector<double>& getVectorX();
		vector<double>& getVectorT();
		void calculateNorms();
		double* getNorms();
		double getTimeMax();
		virtual void printResults() = 0;
		virtual void calculateNumericalSolution() = 0; // add const = 0  at the end ?
};

#endif