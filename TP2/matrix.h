// surcharge des operateur de calcul matriciel

#include <cmath>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

//multiplication d'une matrice par un scalaire
template <typename T1, typename T2>
vector<vector<T2> > operator*(const T1 & x, const vector<vector<T2> >& y){
	vector<vector<T2> > z(y.size(), vector<T2>(y.size()));
	for (size_t i = 0; i<y.size(); ++i)
	{
		for (size_t j = 0; j<y.size(); ++j)
		{
			z[i][j] = x * y[i][j];
		}
	}

	return z;
}



//produit matriciel
template <typename T1, typename T2>
vector<vector<T2> > operator*(const vector<vector<T1> > & x, const vector<vector<T2> > & y){
	vector<vector<T2> > z(y.size(), vector<T2>(y.size()));
	double sum;
	for (size_t i = 0; i<y.size(); ++i)
	{
		for (size_t j = 0; j<y.size(); ++j)
		{
			sum = 0.;
			for (size_t k = 0; k<y.size(); ++k)
			{
				sum += x[i][k] * y[k][j];
			}
			z[i][j] = sum;
		}

	}

	return z;
}



//egalite matricielle
template <typename T>
bool operator==(const vector<vector<T> > & x, const vector<vector<T> > & y)
{

	bool b = true;
	int dim = y.size();

	for (int i = 0; i<dim; i++)
	{
		for (int j = 0; j<dim; j++)
		{
			if (x[i][j] != y[i][j])
			{
				b = false;
				break;
			}
		}
		if (b == false)
		{
			break;
		}
	}
	return b;

}








