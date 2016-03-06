#include "Black_Scholes.h"

//approximation of the normal cumulative function (algorithme from  Hart, J.F. et al, 'Computer Approximations', Wiley 1968 , programmer Alan Miller )
double cdfNormal(double d)
{
	// System generated locals
	double ret_val, d__1;

	// Local variables
	double zabs, p, expntl;
	zabs = fabs(d);

	//     |Z| > 37

	if (zabs > 37.) {
		p = 0.;
	}
	else {

		//     |Z| <= 37

		// Computing 2nd power
		d__1 = zabs;
		expntl = exp(-(d__1 * d__1) / 2);

		//     |Z| < CUTOFF = 10/SQRT(2)
		if (zabs < 7.071067811865475)
		{
			p = expntl * ((((((zabs * .03526249659989109 + .7003830644436881)
				* zabs + 6.37396220353165) * zabs + 33.912866078383) *
				zabs + 112.0792914978709) * zabs + 221.2135961699311) *
				zabs + 220.2068679123761) / (((((((zabs *
				.08838834764831844 + 1.755667163182642) * zabs +
				16.06417757920695) * zabs + 86.78073220294608) * zabs +
				296.5642487796737) * zabs + 637.3336333788311) * zabs +
				793.8265125199484) * zabs + 440.4137358247522);

			//     |Z| >= CUTOFF
		}
		else {
			p = expntl / (zabs + 1 / (zabs + 2 / (zabs + 3 / (zabs + 4 / (
				zabs + .65))))) / 2.506628274631001;
		}
	}
	if (d > 0.) {
		p = 1 - p;
	}
	ret_val = p;
	return (ret_val);
}


//calculate the price of an option (call or put) using the black scholes formula
double callput(double spot, double strike, double T, double r, double q, double vol, int CallPut)
{

	double totalVolatility = vol*sqrt(T);
	double d1 = (log(spot / strike) + (r - q)*T) / totalVolatility + totalVolatility / 2.0;
	double d2 = d1 - vol*sqrt(T);
	double price = CallPut * spot*exp(-q*T)*cdfNormal(CallPut * d1) - CallPut * strike*exp(-r*T)*cdfNormal(CallPut * d2);

	return price;
}





