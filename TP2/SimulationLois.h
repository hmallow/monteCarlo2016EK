#include <math.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <tchar.h>
#include <stdio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define M_PI 3.14159265358979323846


using namespace std;

// Simuler une loi uniforme
double loiuniforme();

// Simule deux lois normales independantes par la methode de Box-muller
vector<double> loinormale();
