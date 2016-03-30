#include <cmath>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
//#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "Black_Scholes.h"

using namespace std;

//simulation d'une trajectoire
vector<vector<double>> Sim_S_M(int Nt, double vol, double spot, double r, double K, double T);

/*
//Simulation de nbSim trajectoires
vector<vector<double>> Paths(int nbSim, int Nt, double vol, double spot, double r, double K, double T);

// Montec-Carlo sur une matrice de trajectoires
double MC_Put(vector<vector<double>> Path, double lambda, double r, double K, double T);

// trouve le lambda qui minimise la fonction renvoie le lambda minimum est le resultat du Monte-Carlo correspondant

vector<double> minlambda_MC(double seuil, double a, double b, int nbSim, int Nt, double vol, double spot, double r, double K, double T);
*/
