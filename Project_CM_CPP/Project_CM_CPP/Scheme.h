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
		std::vector<double> initialCondition;
		std::vector<double> leftBoundryCondition;
		std::vector<double> rightBoundryCondition;
		Matrix NumericalResult;
		Matrix AnalyticalResult;
	public:
		void calculateAnalyticalResult();
		Scheme();
		Scheme(double dt,double dx);
		Matrix& getAnalytical();
		double getU();
		double getDeltaT();
		double getDeltaX();
		Matrix& getNumerical();
		void setNumerical(Matrix newNumerical);
		void initialAndBoundry();
		std::vector<double>& getVectorX();
		std::vector<double>& getVectorT();
		std::vector<double>& getInitial();
		std::vector<double>& getLeftBoundry();
		std::vector<double>& getRightBoundry();
		virtual void calculateNumericalSolution() = 0; // add const = 0  at the end ?
};