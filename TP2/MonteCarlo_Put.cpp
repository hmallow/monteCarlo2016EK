
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "MonteCarlo_Put.h"
#include "vector.h"
#include "SimulationLois.h"
#include "Black_Scholes.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAXIT 300

using namespace std;


vector<double> Sim_S_M(int Nt, double vol, double spot, double r, double K, double T)
{
<<<<<<< HEAD
	int index = INFINITY;

	double delta_t = T / Nt;

	vector<double> lnS(Nt + 1, 0.);
	vector<double> S(Nt + 1, 0.);
	vector<double> M(Nt + 1, 0.);


	// Initialisation
	lnS[0] = log(spot);
	S[0] = spot;
	M[0] = 0;

	// Boucle discretisation
	for (int nt = 1; nt < (Nt + 1); nt++)
	{
		// Calcul le spot aux instants de discretisation
		double normale = loinormale()[0];
		lnS[nt] = lnS[nt - 1] + vol*sqrt(delta_t)*normale + (r - vol*vol / 2)*delta_t;
		S[nt] = exp(lnS[nt]);

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
			M[nt] = M[nt - 1] + callput(S[nt], K, T - nt*delta_t, r, 0, vol, -1) - callput(S[nt - 1], K, T - (nt - 1)*delta_t, r, 0, vol, -1);
		}
		else
		{
			M[nt] = M[nt - 1];
		}
	}

	S.insert(S.end(), M.begin(), M.end());

	return(S);
=======
    int index=INFINITY;
    
    double delta_t = T / Nt;
    
    vector<double> lnS(Nt + 1, 0.);
    vector<double> S(Nt + 1, 0.);
    vector<double> M(Nt + 1, 0.);
    
    
    // Initialisation
    lnS[0] = log(spot);
    S[0] = spot;
    M[0] = 0;
    
    // Boucle discretisation
    for (int nt = 1; nt < (Nt+1); nt++)
    {
        // Calcul le spot aux instants de discretisation
        double normale = loinormale()[0];
        lnS[nt] = lnS[nt-1] + vol*sqrt(delta_t)*normale + (r - vol*vol / 2)*delta_t;
        S[nt] = exp(lnS[nt]);
        
        // Calcul l'indice minimum quand le spot est en dessous du strike
        if ((S[nt] <= K) && (nt<index))
        {
            index = nt;
        }
        else
        {
        }
        
        // Calcul les valeurs de la martingale choisie
        if (nt>=index)
        {
            M[nt] = M[nt - 1] + callput(S[nt], K, T-nt*delta_t, r, 0, vol, -1) - callput(S[nt - 1], K,T-(nt - 1)*delta_t, r, 0, vol, -1);
        }
        else
        {
            M[nt] = M[nt - 1];
        }
    }
    
    S.insert(S.end(), M.begin(), M.end());
    
    return(S);
>>>>>>> origin/master
}




vector<vector<double>> Paths(int nbSim, int Nt, double vol, double spot, double r, double K, double T)
{
<<<<<<< HEAD
	vector<vector<double>> Path(nbSim, vector<double>(2 * (Nt + 1), 0.));

	for (int i = 0; i<nbSim; i++)
	{
		Path[i] = Sim_S_M(Nt, vol, spot, r, K, T);
	}

	return(Path);
=======
    vector<vector<double>> Path(nbSim, vector<double>(2*(Nt+1), 0.));
    
    for (int i = 0; i<nbSim; i++)
    {
        Path[i] = Sim_S_M(Nt, vol, spot, r, K, T);
    }
    
    return(Path);
>>>>>>> origin/master
}

double MC_Put(vector<vector<double>> Path, double lambda, double r, double K, double T)
{
<<<<<<< HEAD
	double PayoffsCV = 0;
	int nbSim = Path.size();
	int l = Path[0].size();
	int Nt = l / 2 - 1;
	double delta_t = T / Nt;

	double maximum;


	vector<double> V(Nt + 1, 0.);


	for (int i = 0; i<nbSim; i++)
	{
		vector<double> Pathi = Path[i];

		vector<double>::const_iterator first = Pathi.begin();
		vector<double>::const_iterator last = Pathi.begin() + Nt + 1;
		vector<double> S(first, last);

		vector<double>::const_iterator first2 = Pathi.begin() + Nt + 1;
		vector<double>::const_iterator last2 = Pathi.begin() + 2 * (Nt + 1);
		vector<double> M(first2, last2);

		for (int nt = 0; nt < (Nt + 1); nt++)
		{
			V[nt] = exp(-r*nt*delta_t)* MAX(K - S[nt], 0) - lambda*M[nt];
		}

		maximum = *max_element(V.begin(), V.end());

		PayoffsCV = PayoffsCV + maximum / nbSim;
	}

	return(PayoffsCV);
=======
    double PayoffsCV = 0;
    int nbSim=Path.size();
    int l=Path[0].size();
    int Nt = l / 2 - 1;
    double delta_t = T / Nt;
    
    double maximum;
    
    
    vector<double> V(Nt + 1, 0.);
    
    
    for (int i = 0; i<nbSim; i++)
    {
        vector<double> Pathi = Path[i];
        
        vector<double>::const_iterator first = Pathi.begin();
        vector<double>::const_iterator last = Pathi.begin() + Nt +1;
        vector<double> S(first, last);
        
        vector<double>::const_iterator first2 = Pathi.begin() + Nt + 1;
        vector<double>::const_iterator last2 = Pathi.begin() + 2 *(Nt+1);
        vector<double> M(first2, last2);
        
        for (int nt = 0; nt < (Nt+1); nt++)
        {
            V[nt] = exp(-r*nt*delta_t)* MAX(K - S[nt], 0) - lambda*M[nt];
        }
        
        maximum = *max_element(V.begin(), V.end());
        
        PayoffsCV = PayoffsCV +  maximum/ nbSim;
    }
    
    return(PayoffsCV);
>>>>>>> origin/master
}


vector<double> minlambda_MC(double seuil, double a, double b, int nbSim, int Nt, double vol, double spot, double r, double K, double T)
{
<<<<<<< HEAD
	vector<double> res(2, 0.);

	// On simule nbSim trajectoires
	vector<vector<double>> Path = Paths(nbSim, Nt, vol, spot, r, K, T);

	// Initialisation 
	double x0 = MIN(a, b);
	double x3 = MAX(a, b);
	double m = (a + b) / 2;
	double lg = x3 - x0;
	double x1 = m - lg / 2;
	double x2 = m + lg / 2;
	int i = 0;

	while (((x3 - x0) > seuil) && (i < MAXIT))
	{
		if ((MC_Put(Path, x2, r, K, T) - MC_Put(Path, x3, r, K, T)) / (x2 - x3) <= 0)
		{
			x0 = x2;
		}
		else if ((MC_Put(Path, x1, r, K, T) - MC_Put(Path, x2, r, K, T)) / (x1 - x2) <= 0)
		{
			x0 = x1;
		}
		else if ((MC_Put(Path, x0, r, K, T) - MC_Put(Path, x1, r, K, T)) / (x0 - x1) <= 0)
		{
			x3 = x2;
		}
		else
		{
			x3 = x1;
		}

		double m = (x0 + x3) / 2;
		double lg = x3 - x0;
		double x1 = m - lg / 2;
		double x2 = m + lg / 2;

		i = i + 1;
	}

	res[0] = m;
	res[1] = MC_Put(Path, res[0], r, K, T);

	return(res);
}


=======
    vector<double> res(2, 0.);
    
    // On simule nbSim trajectoires
    vector<vector<double>> Path = Paths(nbSim, Nt, vol, spot, r, K, T);
    
    // Initialisation
    double x0 = MIN(a,b);
    double x3 = MAX(a,b);
    double m = (a + b) / 2;
    double lg = x3 - x0;
    double x1 = m - lg / 2;
    double x2 = m + lg / 2;
    int i = 0;
    
    while (((x3 - x0) > seuil) && (i < MAXIT))
    {
        if ((MC_Put(Path, x2, r, K, T) - MC_Put(Path, x3, r, K, T)) / (x2 - x3) <= 0)
        {
            x0 = x2;
        }
        else if ((MC_Put(Path, x1, r, K, T) - MC_Put(Path, x2, r, K, T)) / (x1 - x2) <= 0)
        {
            x0 = x1;
        }
        else if ((MC_Put(Path, x0, r, K, T) - MC_Put(Path, x1, r, K, T)) / (x0 - x1) <= 0)
        {
            x3 = x2;
        }
        else
        {
            x3 = x1;
        }
        
        double m = (x0 + x3) / 2;
        double lg = x3 - x0;
        double x1 = m - lg / 2;
        double x2 = m + lg / 2;
        
        i = i + 1;
    }
    
    res[0] = m;
    res[1] = MC_Put(Path, res[0], r, K, T);
    
    return(res);
}


>>>>>>> origin/master
