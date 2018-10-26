#include "ThomasAlgorithm.h"
using namespace std;

ThomasAlgorithm::ThomasAlgorithm()
{
	//
}

ThomasAlgorithm::ThomasAlgorithm(double a, double b, double c, int newSize): aCoef(a),bCoef(b),cCoef(c),size(newSize) {}

double ThomasAlgorithm::getACoef()
{
	return this->aCoef;
}

double ThomasAlgorithm::getBCoef()
{
	return this->bCoef;
}

double ThomasAlgorithm::getCCoef()
{
	return this->cCoef;
}

int ThomasAlgorithm::getSize()
{
	return this->size;
}

vector<double> ThomasAlgorithm::solve(vector<double> dVector)
{
	double m = 0;
	vector<double> aVector(this->getSize(),this->getACoef());
	vector<double> bVector(this->getSize(), this->getBCoef());
	vector<double> cVector(this->getSize(), this->getCCoef());
	vector<double> xVector(this->getSize(), 0);
	//Forward elimination phase
	int size=this->getSize();
	for (int i = 1; i < size; i++)
	{
		m = aVector[i] / bVector[i - 1];
		bVector[i] = bVector[i] - (m * cVector[i - 1]);
		dVector[i] = dVector[i] - (m * dVector[i - 1]);
	}
	//Backward substitution phase
	//first we need to calculate first x value
	xVector[size - 1] = dVector[size - 1] / bVector[size - 1];
	for (int i = size - 2; i >= 0; i--)
	{
		xVector[i] = (dVector[i] - cVector[i] * xVector[i + 1]) / bVector[i];
	}
	return xVector;
}