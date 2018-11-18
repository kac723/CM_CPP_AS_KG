#pragma once
#include <vector>
#include <ostream>
#include <string>
#include <fstream>
#include "Matrix.h"

class Scheme
{
	private:
		double deltaT;
		double deltaX;
		const double u = 250;
		const int L = 400;
		const double timeMax = 0.6;
		std::vector<double> xVector;
		std::vector<double> tVector;
		Matrix NumericalResult;
		Matrix AnalyticalResult;
		double norms[3];
	public:
		Scheme();
		Scheme(double dt, double dx);
		void calculateAnalyticalResult();
		double getA();
		Matrix& getNumerical();
		void initialAndBoundry();
		std::vector<double>& getVectorX();
		std::vector<double>& getVectorT();
		void calculateNorms();
		void printResults(std::string schemeMethod);
		virtual void calculateNumericalSolution()=0; // add const = 0  at the end ?
};