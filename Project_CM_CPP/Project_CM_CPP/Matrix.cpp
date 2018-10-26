#include "Matrix.h"

Matrix::Matrix()
{
	(*this).resize(1);
}


Matrix::Matrix(int rows,int col)
{
	(*this).resize(rows);
	for (int i = 0; i < rows; i++)
	{
		(*this)[i].resize(col);
	}
}

Matrix::Matrix(Matrix& copyM)
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

Matrix& Matrix::operator-(const Matrix& subtractMatrix)
{
	Matrix resultMatrix((*this).getCols(),((*this).getRows()));
	Matrix copyMatrix(*this);
	for (int i = 0; i < (*this).size(); i++)
	{
		for (int j = 0; j < (*this)[0].size(); j++)
		{
			resultMatrix[i][j] = copyMatrix[i][j] - subtractMatrix[i][j];
		}
	}
	return resultMatrix;
}

int Matrix::getCols()
{
	return (*this).size();
}

int Matrix::getRows()
{
	return (*this)[0].size();
}

double Matrix::oneNorm()
{
	double sum = 0;
	double NewResult = 0;
	double result = 0;
	for (int n = 0; n < this->getRows(); n++)
	{
		for (int i = 0; i < (*this).getCols(); i++)
		{
			sum += abs((*this)[i][n]); //summing values from one column in loop. 
		}
		NewResult = sum;
		sum = 0;
		if (NewResult > result) //if new result is bigger then previous then we update result value
		{
			result = NewResult;
		}

	}
	return result;
}

double Matrix::twoNorm()
{
	double result = 0;
	for (int i = 0; i < (*this).getCols(); i++)
	{
		for (int n = 0; n < (*this).getRows(); n++)
		{
			result += pow(abs((*this)[i][n]), 2);
		}
	}
	return sqrt(result);
}

double Matrix::uniformNorm()
{
	double sum = 0;
	double NewResult = 0;
	double result = 0;
	for (int i = 0; i < (*this).getCols(); i++)
	{
		for (int n = 0; n < (*this).getRows(); n++)
		{
			sum += abs((*this)[i][n]); //summing values from one row in loop. 
		}
		NewResult = sum;
		sum = 0;
		if (NewResult > result) //if new result is bigger then previous then we update result value
		{
			result = NewResult;
		}

	}
	return result;
}