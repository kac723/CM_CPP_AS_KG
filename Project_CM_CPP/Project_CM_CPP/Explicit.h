#ifndef EXPLICIT_H //Include guard
#define EXPLICIT_H

#include "Scheme.h"

using namespace std;

/**
An explicit class in order to solve the problem with the explicit method 
The Explicit class provides:
* basic constructors for using the explicit method with the Scheme Class.
* or by creating an empty explicit of a given the name of the method(FTBS or LW) deltaT and deltaX.
*/
class Explicit: public Scheme
{	
	private:
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
		* The name of the new method (Type string)
		* The delta T parameter (Time interval) (Type double)
		* The delta X parameter (Space interval) (Type double)
		* @see Explicit()
		*/
		Explicit(string newMethod, double dT, double dx);
		
		// METHOD
		/**
		Function created for future purposes.
		When creating new methods it may be necessary to change space or time limits in different way
		Intialize this function with :
		* The new limit in space (Type int)
		* The new limit in time (Type int)
		*/
		void modifyCaluclationLimits(int &spaceLimit, int &timeLimit);

		// VIRTUAL METHODS
		/**
		This method is a virtual method from abstract class Scheme.
		Calculating numerical result based on method specified in constructor (FTBS or LW).
		As Explicit class inherit from Scheme it must implement this method.
		*/
		virtual void calculateNumericalSolution() ;
};

#endif