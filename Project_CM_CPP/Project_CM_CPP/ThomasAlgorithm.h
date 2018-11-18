#ifndef THOMASALGORITHM_H //Include guard
#define THOMASALGORITHM_H

#include <vector>

using namespace std;

/**
A class in order to use the Thomas algorithm
The Thomas algorithm class provides:
* basic constructors for using the Thomas algorithm.
* or by create empty Thomas Algorythm with coefficients and size.
*/
class ThomasAlgorithm
{
	private:
		double aCoef;
		double bCoef;
		double cCoef;
		int size;

	public:
		// CONSTRUCTORS
		/**
		* Default constructor.  Intialize an empty Thomas algorithm
		* @see ThomasAlgorithm(double a, double b, double c,int size)
		*/
		ThomasAlgorithm();
		/**
		Copy constructor takes an Thomas algorithm reference.
		Intialize this method with:
		* The first coeeficient of the matrix (Type Double)
		* The second coeeficient of the matrix (Type Double)
		* The third coeeficient of the matrix (Type Double)
		* The size of the matrix (Type int)
		* @see ThomasAlgorithm()
		*/
		ThomasAlgorithm(double a, double b, double c,int size);

		// Function
		/**
		Function for solve a tridiagonal system of equations.
		Return a column matrix who caan also condider like a vector.
		@return vector<double>
		*/
		vector<double> solve(vector<double> dVector);

		// Setter functions 
		/**
		
		*/
		void setCoefficients(double newA, double newB, double newC);
		/**
		
		*/
		void setSize(int newSize);

};

#endif