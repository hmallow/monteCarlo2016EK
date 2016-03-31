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
#include "EstimateurMonteCarlo.h"



using namespace std;


int main()
{ 
	double lambda = 1;

	double spot=80;
	double K=100;
	double T = 0.5;
	double r=0.06;
	double vol=0.4;
	int Nt = 50;
	int nbSim = 5000;

	double seuil = 1.0e-2;
	double a = 0.6;
	double b = 1.3;

	double Prixput=callput(spot, K, T, r, 0, vol, -1);

	cout << "Le prix d'un put europeen est : "<< Prixput << endl;
    
    //creation de l'ensemble de minimisation
    vector<shared_ptr<Path>> paths;
    vector<shared_ptr<Path>> marts;
    for (int i = 0; i < 300; i++) {
        auto sim = Sim_S_M(Nt, vol, spot, r, K, T);
        Path Z_path = Path(sim[0]);
        Path M_path = Path(sim[1]);
        paths.push_back(make_shared<Path>(Z_path));
        marts.push_back(make_shared<Path>(M_path));
    }
    SetOfPaths MiniSet = SetOfPaths(paths);
    SetOfPaths MartSet = SetOfPaths(marts);
    
    //Tests
    MCEstimator estim = MCEstimator(make_shared<SetOfPaths>(MiniSet));
    auto sups = MiniSet.computeSups();
    auto Esup = estim.computeMeanSup();
    
    //Recuperation du lambda min
    double l_min = minLambda(MiniSet, MartSet);
    
    cout << "lambda vaut " << l_min << endl;
    
    //creation de l'ensemble de calcul
    vector<shared_ptr<Path>> computePaths;
    for (int i = 0; i < nbSim; i++) {
        auto sim = Sim_S_M(Nt, vol, spot, r, K, T);
        Path path = Path(sim[0]) + Path(sim[1])*(-1*l_min);
        computePaths.push_back(make_shared<Path>(path));
    }
    SetOfPaths ComputeSet = SetOfPaths(computePaths);
    estim.setPaths(make_shared<SetOfPaths>(ComputeSet));
    double prix = estim.computeMeanSup();
    
    cout << "le prix de l'option US est :" << prix <<endl;

	/*vector<vector<double>> Path = Paths(nbSim, Nt, vol, spot, r, K, T);

	double res = MC_Put(Path, lambda, r, K, T);

	cout << "res : " << res << endl;

	vector<double> PutUS = minlambda_MC(seuil, a, b, nbSim, Nt, vol, spot, r, K, T);

	cout << "Le prix d'un put US est : " << PutUS[1] << endl;

	cout << "Le lambda min est : " << PutUS[0] << endl;
    */
	

	return 0;

}

