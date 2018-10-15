class Method 
{
private:
public:
	Method(); // default constructor
	void ExplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT, double u);
	void ImplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT);
	void LaxScheme(double deltaX, double deltaT, vector<vector<double>>& T, int sizeN, int sizeI, double u);
	void ImplicitSchemeFTCS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT);
	void ThomasAlgorithm(vector<double>& a, vector<double>& b, vector<double>& c, vector<double>& x, vector<double>& d, int sizeI);
};

Method::Method()
{

}

void Method::ExplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT, double u)
{

}

void Method::ImplicitUpWindSchemeFTBS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{

}

void Method::LaxScheme(double deltaX, double deltaT, vector<vector<double>>& T, int sizeN, int sizeI, double u)
{

}

void Method::ImplicitSchemeFTCS(vector<vector<double>>& T, int sizeI, int sizeN, double deltaX, double deltaT)
{

}

void Method::ThomasAlgorithm(vector<double>& a, vector<double>& b, vector<double>& c, vector<double>& x, vector<double>& d, int sizeI)
{

}