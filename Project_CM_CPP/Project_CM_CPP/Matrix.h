#ifndef MATRIX_H //Include guard
#define MATRIX_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

/**
A matrix class for data storage of a 2D array of doubles
The implementation is derived from the standard container vector std::vector
We use private inheritance to base our vector upon the library version whilst
allowing usto expose only those base class functions we wish to use - in this
case the array access operator []

The Matrix class provides:
* basic constructors for creating a matrix object from other matrix object,
* or by creating empty matrix of a given size,
* or by copying a matrix 
* basic operations like access via [] operator, and substraction
*/
class Matrix : private vector<vector<double>>
{
private:
	typedef vector<vector<double>> m;

public:
	using m::operator[];

	// CONSTRUCTORS
	/**
	Default constructor.  Intialize an empty Matrix Object
	* @see Matrix(int rows, int col)
	* @see Matrix(const Matrix& copyM)
	*/
	Matrix();
	/**
	Alternative constructor for uil a matrix rows by col.
	Intialize this method with:
	* The number if rows in your new matrix (Type int)
	* The number of columns in your new matrix (Type int)
	* @see Matrix()
	* @see Matrix(const Matrix& copyM)
	*/
	Matrix(int rows, int col);
	/**
	Alternative constructor for opy a matrix.
	Intialize this method with:
	* The name of the matrix of you want to copy (Type Matrix)
	* @see Matrix()
	* @see Matrix(int rows, int col)
	*/
	Matrix(const Matrix& copyM);

	// Norm functions
	/**
	Normal public method that returns a double.
	It returns L1 norm of matrix
	* @see twoNorm()
	* @see uniformNorm()
	* @return double 
	*/
	double oneNorm();
	/**
	Normal public method that returns a double.
	It returns L2 norm of matrix
	* @see oneNorm()
	* @see uniformNorm()
	* @return double 
	*/
	double twoNorm();
	/**
	Normal public method that returns a double.
	It returns L_max norm of matrix
	* @see oneNorm()
	* @see twoNorm()
	* @exception out_of_range ("vector access error")
	* vector has zero size
	* @return double 
	*/
	double uniformNorm();

	// Getter functions
	/**
	* @return number of matrix's columns (Type int)
	*/
	int getCols() const;
	/**
	* @return number of matrix's rows (Type int)
	*/
	int getRows() const;

	/**
	Overloaded substraction operator
	return the result of the substraction of 2 matrix. 
	*/
	Matrix operator-(Matrix subtractMatrix);
};

#endif