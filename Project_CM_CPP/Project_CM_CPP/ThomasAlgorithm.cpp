#include "ThomasAlgorithm.h"
using namespace std;

ThomasAlgorithm::ThomasAlgorithm()
{
	//
}

ThomasAlgorithm::ThomasAlgorithm(double a, double b, double c, vector<double> dV, int size)
{
	this->a.assign(size, a);
	this->b.assign(size, b);
	this->c.assign(size, c);
	this->d = dV;
	this->x.resize(size);
}

std::vector<double> ThomasAlgorithm::getX()
{
	return this->x;
}

void ThomasAlgorithm::solve()
{
	double m = 0;
	//Forward elimination phase
	int size=this->a.size();
	for (int i = 1; i < size; i++)
	{
		m = a[i] / b[i - 1];
		b[i] = b[i] - (m * c[i - 1]);
		d[i] = d[i] - (m * d[i - 1]);
	}
	//Backward substitution phase
	//first we need to calculate first x value
	x[size - 1] = d[size - 1] / b[size - 1];
	for (int i = size - 2; i >= 0; i--)
	{
		x[i] = (d[i] - c[i] * x[i + 1]) / b[i];
	}
}