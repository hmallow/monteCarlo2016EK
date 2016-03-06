// Surcharge des operateurs de calcul vecoriel

#include <cmath>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

//multiplication d'un vecteur par un scalaire
template <typename T1, typename T2>
vector<T2> operator*(const T1 & x, const vector<T2> & y){
	vector<T2> z(y.size());
	for (size_t i = 0; i<y.size(); ++i) z[i] = x * y[i];
	return z;
}




//produit scalaire
template <typename T1, typename T2>
double operator*(const vector<T1> & x, const vector<T2> & y){
	double z = 0.;
	for (size_t i = 0; i<y.size(); ++i) z += x[i] * y[i];
	return z;
}

//addition de vecteurs
template <typename T>
vector<T> operator+(const vector<T> & x, const vector<T> & y){
	vector<T> z(y.size());
	for (size_t i = 0; i<y.size(); ++i) z[i] = x[i] + y[i];
	return z;
}

//soustraction de vecteurs
template <typename T>
vector<T> operator-(const vector<T> & x, const vector<T> & y){
	vector<T> z(y.size());
	for (size_t i = 0; i<y.size(); ++i) z[i] = x[i] - y[i];
	return z;
}
