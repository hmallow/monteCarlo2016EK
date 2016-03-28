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
<<<<<<< HEAD
=======
#include <tchar.h>
>>>>>>> origin/master
#include <stdio.h>


#include "Black_Scholes.h"

using namespace std;

<<<<<<< HEAD
//simulation d'une trajectoire 
vector<double> Sim_S_M(int Nt, double vol, double spot, double r, double K, double T);

//Simulation de nbSim trajectoires
vector<vector<double>> Paths(int nbSim, int Nt, double vol, double spot, double r, double K, double T);

// Monte-Carlo sur une matrice de trajectoires
double MC_Put(vector<vector<double>> Path, double lambda, double r, double K, double T);

// trouve le lambda qui minimise la fonction renvoie le lambda minimum et le resultat du Monte-Carlo correspondant
=======
//simulation d'une trajectoire
vector<double> Sim_S_M(int Nt, double vol, double spot, double r, double K, double T);

//Simulation de nbSim trajectoires
vector<vector<double>> Paths(int nbSim, int Nt, double vol, double spot, double r, double K, double T);

// Montec-Carlo sur une matrice de trajectoires
double MC_Put(vector<vector<double>> Path, double lambda, double r, double K, double T);

// trouve le lambda qui minimise la fonction renvoie le lambda minimum est le resultat du Monte-Carlo correspondant
>>>>>>> origin/master
vector<double> minlambda_MC(double seuil, double a, double b, int nbSim, int Nt, double vol, double spot, double r, double K, double T);

