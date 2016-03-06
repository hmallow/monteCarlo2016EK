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
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "Black_Scholes.h"

using namespace std;

//simulation d'une trajectoire 
double Sim(int Nt, double vol, double spot, double r, double K, double T, double lambda);

//Monte-Carlo pour un put americain
double MC_Put(int nbSim, int Nt, double vol, double spot, double r, double K, double T, double lambda);

// trouve le lambda qui minimise la fonction
double minlambda(double seuil, double inf, double sup, int nbSim, int Nt, double vol, double spot, double r, double K, double T);

// Monte-Carlo pour un put americain avec le lambda min 
double MC_Put_final(int nbSim, int Nt, double vol, double spot, double r, double K, double T, double seuil, double inf, double sup);
