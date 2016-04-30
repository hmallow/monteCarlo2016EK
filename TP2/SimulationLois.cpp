#include "SimulationLois.h"
#include "vector.h"
#include <stdio.h>
#include <random>

using namespace std;
 //test sandra
// coucou cest adrien

/*double loiuniforme()
{
    mt19937::result_type seed = clock();
    auto real_rand = std::bind(std::uniform_real_distribution<double>(0,1), mt19937(seed));
    return real_rand();
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

}*/

std::random_device rd;
std::mt19937 mt(rd());

double loiuniforme()
{
    std::uniform_real_distribution<double> dist(0,1);
    double random_number = dist(mt);
    return random_number;
    //return (double)((float)rand() / (float)RAND_MAX);
}



vector<double> loinormale()
{
    vector<double> loinormales(2, 0.);
    
    double u1 = loiuniforme();
    double v1 = loiuniforme();
    
    loinormales[0] = sqrt(-2 * log(u1))*cos(2 * M_PI*v1);
    loinormales[1] = sqrt(-2 * log(u1))*sin(2 * M_PI*v1);
    
    return(loinormales);
    
}

