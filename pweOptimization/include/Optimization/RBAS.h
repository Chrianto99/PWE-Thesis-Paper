//
// Created by Christos on 6/19/2025.
//

#ifndef PWEOPTIMIZATION_RBAS_H
#define PWEOPTIMIZATION_RBAS_H

#endif //PWEOPTIMIZATION_RBAS_H

#include "set"
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "ParetoHandler.h"
#include "LocalSearch.h"
#include "Algorithm.h"
#include "NSGA-II.h"
using namespace std;

class RBAS{

private:
    Algorithm* algorithm;
    ModeHandler* modeHandler;
    double evaporationRate;
    double intensityFactor;

public:

    RBAS(Algorithm& algorithm,double evaporationRate, double intensityFactor):
    algorithm(&algorithm),
    modeHandler(&algorithm.rayHandler.getModeHandler()),
    evaporationRate(evaporationRate),
    intensityFactor(intensityFactor){
    }

    void run();

    void runBruteForce();

    void updatePheromones(vector<Solution> &ants);

    map<int,set<Solution>> &getOutput(){
        return algorithm->output;
    }


};