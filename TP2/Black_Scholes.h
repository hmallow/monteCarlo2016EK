#include <cmath>

using namespace std;

//approximation of the normal cumulative function (algorithme from  Hart, J.F. et al, 'Computer Approximations', Wiley 1968 , programmer Alan Miller )
double cdfNormal(double d);

//calculate the price of an option (call or put) using the black scholes formula
double callput(double spot, double strike, double T, double r, double q, double vol, int CallPut);


