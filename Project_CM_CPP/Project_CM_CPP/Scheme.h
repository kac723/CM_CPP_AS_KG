#ifndef SCHEME_H //Include guard
#define SCHEME_H

#include <vector>
#include <ostream>
#include <string>
#include "Matrix.h"

using namespace std;

/**
A Scheme class in order to have the function.
This function uses the same variables of the statement.
The Scheme class provides:
* basic constructors for creating a scame object from other schame object,
* or by creating an empty scheme of a given deltaT and deltaX.
* The analytical result wth the inatial and boudry conditions.
* Getter in order to keep the values.
*/
class Scheme
{
	private:
		// Value of the statement 
		const double u = 250;
		const int L = 400;
		const double timeMax = 0.6;

		// Interval
		double deltaT; // Time 
		double deltaX; // Space

		// All the space value
		vector<double> xVector;
		// All the time value
		vector<double> tVector;

		// Numerical result
		Matrix NumericalResult;
		// Analytical result 
		Matrix AnalyticalResult;

		// one norm, two norm and uniform norm
		double norms[3];

	public:
		// CONSTRUCTORS
		/**
		* Default constructor.  Intialize an empty Scheme
		* @see Scheme(double dt, double dx)
		*/
		Scheme();
		/**
		Copy constructor takes an Matrix method reference.
		Allocates required size for vectors and matrixes based on assigned deltaT and deltaX values
		Intialize this method with:
		* The name of the matrix of you want to copy (Type Matrix)
		* @see Matrix()
		* @see Matrix(int rows, int col)
		*/
		Scheme(double dt, double dx);

		// Functions
		/**
		Function for have the wave equation
		* @return A = u*deltaT/deltaX with u a constant = 250
		*/
		double getA();
		/**
		Based on equation from the task description the function:
		Calculates the analytical result
		Stores results in AnalyticalResult matrix
		*/
		void calculateAnalyticalResult();
		/**
		Based on equation from the task description the function apply:
		* Boundry condition. 
		* Initial condition.
		*/
		void initialAndBoundry();
		/**
		Function calculates one norm, two norm and uniform norm and stores results in array norms
		*/
		void calculateNorms();

		// Getter functions 
		/**
		Return the private Matrix AnalyticalResult
		*/
		Matrix& getAnalytical();
		/**
		Return the private Matrix NumericalResult
		*/
		Matrix& getNumerical();
		/**
		Return the private vector<double> tVector
		*/
		vector<double>& getVectorX();
		/**
		Return the private vector<double> tVector
		*/
		vector<double>& getVectorT();
		/**
		Return the private array of double norms
		*/
		double* getNorms();
		/**
		Return the max value of the time 
		*/
		double getTimeMax();

		virtual void printResults() = 0;
		virtual void calculateNumericalSolution() = 0; // add const = 0  at the end ?
};

#endif