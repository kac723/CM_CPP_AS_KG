#ifndef IMPLICIT_H //Include guard
#define IMPLICIT_H

#include "Scheme.h"
#include "ThomasAlgorithm.h"

using namespace std;

/**
An explicit class in order to solve the problem with the implicit method 
The Implicite class provides:
* basic constructors for using the imlicit method with the Scheme Class.
* or by creating an empty implicit of a given the name of the method(FTBS or FTCS) deltaT and deltaX.
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
		Intialize this method with:
		* The name of the new method (Type string)
		* The delta T parameter (Time interval) (Type double)
		* The delta X parameter (Space interval) (Type double)
		* @see Explicit()
		*/
		Implicit(string method, double dT, double dx);

		// VIRTUAL METHODS
		/**
		This method is a virtual method from abstract class Scheme.
		Calculating numerical result based on method specified in constructor (FTBS or FTCS).
		As Implicit class inherit from Scheme it must implement this method.
		*/
		virtual void calculateNumericalSolution();
}; 


#endif