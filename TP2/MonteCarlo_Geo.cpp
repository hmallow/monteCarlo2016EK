#include <stdio.h>
#include <vector>
#include <algorithm>

#include "MonteCarlo_Geo.h"
#include "vector.h"
#include "SimulationLois.h"
#include "Black_Scholes.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAXIT 10

using namespace std;


double SimGeo(int Nt, double vol1, double vol2, double spot1, double spot2, double r, double K, double T, double lambda)
{
	double maximum;
	int index = INFINITY;

	double delta_t = T / Nt;

	vector<double> vols(2,0.);
	vols[0] = vol1;
	vols[1] = vol2;

	double newvol = sqrt(vols*vols)/2;
	double newr = r - newvol*newvol / 2;

	vector<double> S(Nt + 1, 0.);
	vector<double> M(Nt + 1, 0.);
	vector<double> V(Nt + 1, 0.);

	// Initialisation
	S[0] = sqrt(spot1*spot2);
	M[0] = 0;
	V[0] = MAX(K - S[0], 0);

	// Boucle discretisation
	for (int nt = 1; nt < (Nt + 1); nt++)
	{
		// Calcul le spot aux instants de discretisation
		S[nt] = S[0] * exp(newvol*loinormale()[0]*sqrt(nt*delta_t) + (newr - newvol*newvol / 2)*nt*delta_t);

		// Calcul l'indice minimum quand le spot est en dessous du strike
		if ((S[nt] <= K) && (nt<index))
		{
			index = nt;
		}
		else
		{
		}

		// Calcul les valeurs de la martingale choisie
		if (nt >= index)
		{
			M[nt] = M[nt - 1] + callput(S[nt], K, T - nt*delta_t, newr, 0, newvol, -1) - callput(S[nt - 1], K, T - (nt - 1)*delta_t, newr, 0, newvol, -1);
		}
		else
		{
			M[nt] = M[nt - 1];
		}

		V[nt] = exp(-r*nt*delta_t)* MAX(K - S[nt], 0) - lambda*M[nt];
	}

	maximum = *max_element(V.begin(), V.end());

	return(maximum);
}




double MC_Geo(int nbSim, int Nt, double vol1, double vol2, double spot1, double spot2, double r, double K, double T, double lambda)
{
	double PayoffsCV = 0;

	for (int i = 0; i<nbSim; i++)
	{
		PayoffsCV = PayoffsCV + SimGeo(Nt, vol1, vol2, spot1, spot2, r, K, T, lambda) / nbSim;
	}

	return(PayoffsCV);
}


double minlambdaGeo(double seuil, double inf, double sup, int nbSim, int Nt, double vol1, double vol2, double spot1, double spot2, double r, double K, double T)
{
	double lambda = 0;
	double lambdaInf = inf;
	double lambdaSup = sup;

	double mid = (lambdaInf + lambdaSup) / 2;

	for (int i = 0; i < MAXIT; i++)
	{

		if (abs(MC_Geo(nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T, mid) - MC_Geo(nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T, lambda)) < seuil)
		{
			return mid;
		}
		else if (MC_Geo(nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T, mid) - MC_Geo(nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T, lambda) > 0)
		{
			lambdaInf = lambda;
		}
		else
		{
			lambdaSup = lambda;
		}

		lambda = mid;

		mid = (lambdaInf + lambdaSup) / 2;

	}

	return(mid);
}


double MC_Geo_final(int nbSim, int Nt, double vol1, double vol2, double spot1, double spot2, double r, double K, double T, double seuil, double inf, double sup)
{
	double PayoffsCV = 0;

	double lambda = minlambdaGeo(seuil, inf, sup, nbSim, Nt, vol1, vol2, spot1, spot2, r, K, T);

	for (int i = 0; i<nbSim; i++)
	{
		PayoffsCV = PayoffsCV + SimGeo(Nt, vol1, vol2, spot1, spot2, r, K, T, lambda) / nbSim;
	}

	return(PayoffsCV);
}
