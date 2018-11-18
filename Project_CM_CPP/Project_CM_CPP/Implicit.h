#ifndef IMPLICIT_H //Include guard
#define IMPLICIT_H

#include "Scheme.h"
#include "ThomasAlgorithm.h"

using namespace std;

/**
An explicit class in order to solve the problem with the implicit method 
The Implicite class provides:
* basic constructors for using the imlicit method with the Scheme Class.
*/
class Implicit :public Scheme
{
	private:
		string method;
		ThomasAlgorithm TA;

	public:
		// CONSTRUCTORS
		/**
		* Default constructor.  Intialize an empty Implicit Method
		* @see Implicit(string newMethod, double dT, double dx)
		*/
		Implicit();
		/**
		Copy constructor takes an Implicit method reference.
		Intialize this method with:
		* The name of the new method (Type string)
		* The delta T parameter (Time interval) (Type double)
		* The delta X parameter (Space interval) (Type double)
		* @see Explicit()
		*/
		Implicit(string method, double dT, double dx);

		virtual void calculateNumericalSolution();
		virtual void printResults();

}; 


#endif