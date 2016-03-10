//#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include<cmath>
#include<iostream>

#include "vector.h"
#include "Black_Scholes.h"
#include "MonteCarlo_Put.h"
#include "MonteCarlo_Geo.h"
#include "SimulationLois.h"



using namespace std;


int main()
{ 

    double lambda = 1.045;

	double spot=80;
	double K=100;
	double T = 0.5;
	double r=0.06;
	double vol=0.4;
	int Nt = 50;
	int nbSim = 1000;

	double seuil = 1.0e-3;
	double inf = 0.5;
	double sup = 1.6;

	double spot1 = 80;
	double spot2 = 80;
	double vol1 = 0.4;
	double vol2 = 0.4;

	

	double Prixput=callput(spot, K, T, r, 0, vol, -1);

	cout << "Le prix d'un put europeen est : "<< Prixput << endl;


	double mc = MC_Put(nbSim, Nt, vol, spot, r, K, T, lambda);

	cout << "Le prix du put us est : " << mc << endl;

	//double l = minlambda(seuil, inf, sup, nbSim, Nt, vol, spot, r, K, T);

	//cout << "Le lambda min est : " << l << endl;

	//double mcf = MC_Put_final(nbSim, Nt, vol, spot, r, K, T, seuil, inf, sup);

	//cout << "Le prix du put americain est : " << mcf << endl;

	double mcgeo = MC_Geo(nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T, lambda);

	cout << "Le prix du put geometrique us est : " << mcgeo << endl;

	//double lgeo = minlambdaGeo(seuil, inf, sup, nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T);

	//cout << "Le lambda min geo est : " << lgeo << endl;

	//double mcfgeo = MC_Geo_final(nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T, seuil, inf, sup);

	//cout << "Le prix du put geo americain est : " << mcfgeo << endl;


	return 0;

}

