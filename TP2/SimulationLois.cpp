#include "SimulationLois.h"
#include "vector.h"
#include <stdio.h>


using namespace std;


double loiuniforme()
{
	return (double)((float)rand() / (float)RAND_MAX);
}


vector<double> loinormale()
{
	vector<double> loinormales(2, 0.);

	double x1;
	double x2;
	double w;
	double n1;
	double n2;

	do
	{
		x1 = 2.0 * loiuniforme() - 1.0;
		x2 = 2.0 * loiuniforme() - 1.0;
		w = x1 * x1 + x2 * x2;
		n1 = sqrt(-2.0 * log(w) / w)*x1;
		n2 = sqrt(-2.0 * log(w) / w)*x2;

	} while ((w >= 1.0) || (w <= 0));

	loinormales[0] = n1;
	loinormales[1] = n2;

	return(loinormales);

}
