#ifndef EXPLICIT_H //Include guard
#define EXPLICIT_H

#include "Scheme.h"

using namespace std;

/**
An explicit class in order to sole the problem with the explicit upwind method 
The Explicit class provides:
* basic constructors for using the explicit method with the Scheme Class.
*/
class Explicit: public Scheme
{	
	private:
		/**
		The name of this new method 
		*/
		string method;
		double (*functionPtr)(double, Matrix&,int,int);

	public:
		// CONSTRUCTORS
		/**
		* Default constructor.  Intialize an empty Explicit Method
		* @see Explicit(string newMethod, double dT, double dx)
		*/
		Explicit();

		/**
		Copy constructor takes an Explicit method reference.
		Intialize this method with:
		* The name of the new method
		* The delta T parameter (Time interval)
		* The delta X parameter (Space interval)
		* @see Explicit()
		*/
		Explicit(string newMethod, double dT, double dx);

		virtual void calculateNumericalSolution() ;
		virtual void printResults();

		/**
		Function created for future purposes. 
		When creating new methods it may be necessary to change space or time limits in different way
		Intialize this function with :
		* The new limit in space (Type int)
		* The new limit in time (Type int)
		*/
		void modifyCaluclationLimits(int &spaceLimit, int &timeLimit);
};

#endif