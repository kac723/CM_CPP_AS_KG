#pragma once
#include <vector>
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
		std::vector<double> norms;
	public:
		Scheme();
		Scheme(double dt, double dx);
		void calculateAnalyticalResult();
		Matrix& getAnalytical();
		double getA();
		Matrix& getNumerical();
		void setNumerical(Matrix newNumerical);
		void initialAndBoundry();
		std::vector<double>& getVectorX();
		std::vector<double>& getVectorT();
		void calculateNorms();
		virtual void calculateNumericalSolution()=0; // add const = 0  at the end ?
};