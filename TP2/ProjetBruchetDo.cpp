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
#include "MultiLevel.h"
#include "MLevel.h"

#include <memory>



using namespace std;


int main()
{ 
	double lambda = 1;

	double spot=120;
	double K=100;
	double T = 0.5;
	double r=0.06;
	double vol=0.4;
	int Nt = 50;
	int nbSim = 5000;

    double seuil = 1.0e-3;
	double a = 0.6;
	double b = 1.3;
    
    auto points = Sim_S(Nt, 5, vol, spot, r, T);

	double Prixput=callput(spot, K, T, r, 0, vol, -1);
    
    
    for (int i = 0; i < 10; i++) {
        cout << loiuniforme() << endl;
    }
    
    /*test
    
    Path path1 = Path(points);
    Path path2 = Path(points);
    
    Path path3 = Path(path2);
    
    vector<shared_ptr<Path>> vectounet;
    vectounet.push_back(make_shared<Path>(path1));
    vectounet.push_back(make_shared<Path>(path2));
    SetOfPaths setOP = SetOfPaths(vectounet);
    //setOP.massConvertToPut(K);
    auto arg = make_shared<SetOfPaths>(setOP);
    vector<shared_ptr<SetOfPaths>> args;
    args.push_back(arg);
    args.push_back(arg);
    vector<int> lolz;
    lolz.push_back(1);
    lolz.push_back(2);
    MultiLevel test = MultiLevel(3, lolz, lolz, args);
    
    //fin test*/

	cout << "Le prix d'un put europeen est : "<< Prixput << endl;
    
    //creation de l'ensemble de minimisation
    vector<shared_ptr<Path>> paths;
    //vector<shared_ptr<Path>> S_paths;
    vector<shared_ptr<Path>> marts;
    for (int i = 0; i < 300; i++) {
        auto sim = Sim_S_M(Nt, vol, spot, r, K, T);
        //Path S_path = Path(sim[0]);
        //S_paths.push_back(make_shared<Path>(S_path));
        Path Z_path = Path(sim[0]);
        Z_path.convertPut(K);
        Path M_path = Path(sim[1]);
        paths.push_back(make_shared<Path>(Z_path));
        marts.push_back(make_shared<Path>(M_path));
    }
    //SetOfPaths SJSet = SetOfPaths(S_paths);
    //SetOfPaths TestPut = SetOfPaths(SJSet.massExtractPut(K));
    SetOfPaths MiniSet = SetOfPaths(paths);
    SetOfPaths MartSet = SetOfPaths(marts);
    
    //Tests
    MCEstimator estim = MCEstimator(make_shared<SetOfPaths>(MiniSet));
    auto sups = MiniSet.computeSups();
    auto Esup = estim.computeMeanSup();
    
    //multilevel
    
    //simulation Option Européenne
    /*vector<double> EuroPoints;
    for (int k = 0; k < Nt; k++) {
        double P_t = callput(spot, K,k*T/Nt, r, 0, vol, -1);
        EuroPoints.push_back(P_t);
    }
    Path EuroPath = Path(EuroPoints);
    EuroPath.discountPath(T, r);*/
    
    cout << "go multilevel" << endl;
    
    vector<int> k_L;
    k_L.push_back(50);
    k_L.push_back(40);
    k_L.push_back(80);
    k_L.push_back(160);
    
    vector<int> n_L;
    n_L.push_back(6600);
    n_L.push_back(43);
    n_L.push_back(21);
    n_L.push_back(10);
    
    vector<SetOfPaths> underlyings;
    
    for (int l = 0; l < 4; l++) {
        SetOfPaths SOP_l;
        for (int i = 0; i < n_L[l]; i++) {
            auto sim = Sim_S_M(Nt, vol, spot, r, K, T);
            Path S_path = sim[0];
            SOP_l.addPath(S_path);
        }
        underlyings.push_back(SOP_l);
    }
    cout << "underlyings créés "<<endl;
    
    MLevel Multilev = MLevel(K, k_L, n_L, underlyings);
    double y_0 = Multilev.first_step();
    double y_n_k = Multilev.next_steps();
    double price = y_0 + y_n_k;
    cout << "le prix de l'option US est :" << price <<endl;
    
    
    /*MultiLevel ML = MultiLevel(3, k_L, n_L, underlyings);
    ML.computeTaus(EuroPath);
    double price = ML.next_steps();
    cout << "le prix de l'option US est :" << price <<endl;*/
    
    
    //fin multilevel
    //Recuperation du lambda min
    //double l_min = minLambda(MiniSet, MartSet);
    
    double l_min = 1;
    
    cout << "lambda vaut " << l_min << endl;
    
    //creation de l'ensemble de calcul
    vector<shared_ptr<Path>> computePaths;
    for (int i = 0; i < 5000; i++) {
        //cout << i << endl;
        auto sim = Sim_S_M(Nt, vol, spot, r, K, T);
        Path Z_path = Path(sim[0]);
        Z_path.convertPut(K);
        Z_path.discountPath(T,r);
        Path path = Z_path + Path(sim[1])*(-1*l_min);
        //auto m = path.getMax();
        computePaths.push_back(make_shared<Path>(path));
    }
    
    SetOfPaths ComputeSet = SetOfPaths(computePaths);
    cout << "set created" << endl;
    
    
    shared_ptr<SetOfPaths> ComputeSetPtr = make_shared<SetOfPaths>(ComputeSet);
    cout << "pointer created" << endl;
    MCEstimator estimBis = MCEstimator(ComputeSetPtr);
    //estim.setPaths(make_shared<SetOfPaths>(ComputeSet));
    cout << "estimator created" << endl;
    double prix = estimBis.computeMeanSup();
    
    cout << "le prix de l'option US est :" << prix <<endl;
    


	return 0;

}

