class Norm
{
private:
public:
	Norm(); // default constructor
	double one_norm(vector<vector<double>>& T, int sizeI, int sizeN);
	double two_norm(vector<vector<double>>& T, int sizeI, int sizeN);
	double uniform_norm(vector<vector<double>>& T, int sizeI, int sizeN);
};

Norm::Norm()
{

}

double Norm::one_norm(vector<vector<double>>& T, int sizeI, int sizeN) 
{
	double sum = 0;
	double NewResult = 0;
	double result = 0;
	for (int n = 0; n < sizeN; n++)
	{
		for (int i = 0; i < sizeI; i++)
		{
			sum += abs(T[i][n]); //summing values from one column in loop. 
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

double Norm::two_norm(vector<vector<double>>& T, int sizeI, int sizeN)
{
	double result = 0;
	for (int i = 0; i < sizeI; i++)
	{
		for (int n = 0; n < sizeN; n++)
		{
			result += pow(abs(T[i][n]), 2);
		}
	}
	return sqrt(result);
}

double Norm::uniform_norm(vector<vector<double>>& T, int sizeI, int sizeN)
{
	double sum = 0;
	double NewResult = 0;
	double result = 0;
	for (int i = 0; i < sizeI; i++)
	{
		for (int n = 0; n < sizeN; n++)
		{
			sum += abs(T[i][n]); //summing values from one row in loop. 
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
