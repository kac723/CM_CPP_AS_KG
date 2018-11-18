#include "Matrix.h"

// Constructors 

Matrix::Matrix()
{
	(*this).resize(1); // default constructor
}

//  Constructor for create a matrix with the number of rows and column
Matrix::Matrix(int rows,int col)
{
	(*this).resize(rows);
	for (int i = 0; i < rows; i++)
	{
		(*this)[i].resize(col);
	}
}

// Constructor for copy a matrix  
Matrix::Matrix(const Matrix& copyM)
{
	(*this).resize(copyM.getCols());
	for (int i = 0; i < copyM.getCols(); i++)
	{
		(*this)[i].resize(copyM.getRows());
	}
	for (int i = 0; i < copyM.getCols(); i++)
	{
		for (int j = 0; j < copyM.getRows(); j++)
		{
			(*this)[i][j] = copyM[i][j];
		}
	}
}

Matrix Matrix::operator-(Matrix subtractMatrix)
{
	Matrix resultMatrix((*this).getCols(),((*this).getRows()));
	for (int i = 0; i < (*this).size(); i++)
	{
		for (int j = 0; j < (*this)[0].size(); j++)
		{
			resultMatrix[i][j] = (*this)[i][j] - subtractMatrix[i][j];
		}
	}
	return resultMatrix;
}

// 1 norm
double Matrix::oneNorm()
{
	// Variables
	double sum = 0;
	double NewResult = 0;
	double result = 0;

	// Calcul of the norm 
	for (int n = 0; n < this->getRows(); n++)
	{
		//summing values from one column in loop.
		for (int i = 0; i < (*this).getCols(); i++)
		{
			sum += abs((*this)[i][n]);  
		}
		NewResult = sum;
		sum = 0;
		//if new result is bigger then previous then we update result value
		if (NewResult > result) 
		{
			result = NewResult;
		}

	}
	return result/(this->getCols()*this->getRows());
}

// 2 norm
double Matrix::twoNorm()
{
	// Variable
	double result = 0;

	// Calcul of the norm
	for (int i = 0; i < (*this).getCols(); i++)
	{
		for (int n = 0; n < (*this).getRows(); n++)
		{
			result += pow(abs((*this)[i][n]), 2);
		}
	}
	return sqrt(result) / (this->getCols()*this->getRows());
}

// Uniform (infinity) norm
double Matrix::uniformNorm()
{
	// Variables 
	double sum = 0;
	double NewResult = 0;
	double result = 0;
	
	// Calcul of the norm 
	for (int i = 0; i < (*this).getCols(); i++)
	{
		//summing values from one row in loop.
		for (int n = 0; n < (*this).getRows(); n++)
		{
			sum += abs((*this)[i][n]);  
		}
		NewResult = sum;
		sum = 0;
		//if new result is bigger then previous then we update result value
		if (NewResult > result) 
		{
			result = NewResult;
		}

	}
	return result / (this->getCols()*this->getRows());
}

// Getteur functions
int Matrix::getCols() const
{
	return (*this).size(); // get the number of columns
}

int Matrix::getRows() const
{
	return (*this)[0].size();// get the number of rows 
}