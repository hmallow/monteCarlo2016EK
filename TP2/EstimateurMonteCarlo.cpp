//
//  EstimateurMonteCarlo.cpp
//  MonteCarlo
//
//  Created by Adrien Bruchet on 29/03/2016.
//  Copyright (c) 2016 Adrien Bruchet. All rights reserved.
//

#include "EstimateurMonteCarlo.h"

#include <memory>

using namespace std;


MCEstimator::MCEstimator(){
    MCPaths = make_shared<SetOfPaths>();
    
}

MCEstimator::MCEstimator(shared_ptr<SetOfPaths> SOPaths){
    
    MCPaths = SOPaths;
}


MCEstimator::~MCEstimator(){
    
}

void MCEstimator::setPaths(shared_ptr<SetOfPaths> const& newSetPaths){
    MCPaths = newSetPaths;
}

std::shared_ptr<SetOfPaths> & MCEstimator::getPaths(){
    return MCPaths;
}

void MCEstimator::addPath(Path & path){
    MCPaths->addPath(path);
}

//calcule l'esperance du sup empirique
double MCEstimator::computeMeanSup(){
    double mean = 0;
    vector<double> sups = MCPaths->computeSups();
    int N = sups.size();
    for (int i = 0; i < N; i++) {
        mean += sups[i];
    }
    mean = double(mean/N);
    return mean;
}

double MCEstimator::computeMean(){
    double mean = 0;
    int N = MCPaths->getPaths().size();
    for (int i = 0; i < N; i++) {
        mean += MCPaths->getPath(i)->getLast();
    }
    mean = double(mean/N);
    return mean;
}

double MCEstimator::computeMean(const vector<double> & points){
    double sum (0);
    int N = points.size();
    for (int i = 0 ; i < N; i++) {
        sum += points[i];
    }
    double res = sum/double(N);
    return res;
}

double minLambda(SetOfPaths const& Z, SetOfPaths const& martingales){
    
    //initialisation
    double epsilon = 1e-2;
    double l_min = -10;
    double l_max = 10;
    double min = l_min;
    double max = l_max;
    double max_it = 1e3;
    int it = 0;
    MCEstimator estim = MCEstimator();
    
    //boucle de dichotomie
    while (it < max_it && (max-min) > epsilon) {
        double d = 0.25*(3*min + max);
        double c = 0.5*(min + max);
        double e = 0.25*(3*max + min);
        
        //calcul en c
        shared_ptr<SetOfPaths> M_ptr = make_shared<SetOfPaths>(Z-martingales*c);
        estim.setPaths(M_ptr);
        double val_c = estim.computeMeanSup();
        
        //calcul en d
        M_ptr = make_shared<SetOfPaths>(Z-martingales*d);
        estim.setPaths(M_ptr);
        double val_d = estim.computeMeanSup();
        
        //calcul en e
        M_ptr = make_shared<SetOfPaths>(Z-martingales*e);
        estim.setPaths(M_ptr);
        double val_e = estim.computeMeanSup();
        
        //comparaison
        if (val_c > val_e) {
            min = c;
        }
        else if (val_d < val_c){
            max = c;
        }
        else{
            min = d;
            max = e;
        }
        it++;
        
    }
    return 0.5*(max + min);
}

double getMax(vector<double> vect){
    double max = vect[0];
    for(double elem:vect){
        if (elem > max){
            max = elem;
        }
    }
    return max;
}


Path compute_M_k(Path const& traj,int nbSim, double strike, double T, double r){
    vector<double> z_points = traj.extractPut(strike);
    Path Z_traj = Path(z_points);
    Z_traj.discountPath(T,r);
    int J = traj.Points().size();
    double time_step = T/double(J-1);
    
    double L_inf = (2*0.06*strike)/(2*0.06+pow(0.4, 2));
    
    //calcul des temps d'exercices
    vector<double> taus;
    for (int j = 0; j < J+1 ; j++) {
        int k = j;
        bool found = false;
        while (found == false && k < J) {
            vector<double> eurotraj;
            for (int p = k; p < J+1; p++) {
                double spot = traj.getPoint(p);
                eurotraj.push_back(callput(spot, strike, (J-p)*time_step, r, 0, 0.4, -1)*exp(-r*(p-k)*time_step));
            }
            if (getMax(eurotraj) >= Z_traj.getPoint(k)) {
                found = true;
                taus.push_back(k);
            }
            else{
                k++;
            }
        }
        if (k == J && found == false) {
            taus.push_back(k);
        }
    }
    
    //calcul des ∆i et de la martingale M_k
    vector<double> M_points;
    M_points.push_back(0);
    vector<double> inner_traj;
    vector<double> inner_traj_1;
    MCEstimator Estim;
    double sum = 0;
    for (int j = 1; j < J; j++) {
        for (int k = 0; k<nbSim; k++) {
            /*vector<double> inner_sim = Sim_S(50, taus[j], 0.4, traj.getPoint(j), r, T);
            Path inner_path = Path(inner_sim);
            inner_path.convertPut(strike);
            double inner_point = inner_path.getLast()*exp(-r*(taus[j]-j)*time_step);
            inner_traj.push_back(inner_point);
            vector<double> inner_sim_1 = Sim_S(50, taus[j], 0.4,traj.getPoint(j-1) , r, T);
            Path inner_path_1 = Path(inner_sim_1);
            inner_path_1.convertPut(strike);
            double inner_point_1 = inner_path_1.getLast()*exp(-r*(taus[j]-(j-1))*time_step);
            inner_traj_1.push_back(inner_point_1);*/
            double inner_point = (strike - Sim_S(50, taus[j], 0.4, traj.getPoint(j), r, T).back())*exp(-r*(taus[j] - j)*time_step);
            if (inner_point < 0) {
                inner_point = 0;
            }
            double inner_point_1 = (strike - Sim_S(50, taus[j], 0.4, traj.getPoint(j-1), r, T).back())*exp(-r*(taus[j] - j+1)*time_step);
            if (inner_point_1 < 0) {
                inner_point_1 = 0;
            }
            inner_traj.push_back(inner_point);
            inner_traj_1.push_back(inner_point_1);
            
        }
        double esp_fi = Estim.computeMean(inner_traj);
        double esp_fi_1 = Estim.computeMean(inner_traj_1);
        double delta_i = esp_fi-esp_fi_1;
        sum = sum + delta_i;
        M_points.push_back(sum);
    }
    cout << "martingale simulee" << endl;
    Path M_k = Path(M_points);
    return M_k;
}



