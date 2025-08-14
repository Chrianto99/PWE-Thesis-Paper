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

class RBAS {

private:
    Algorithm *algorithm;
    ModeHandler *modeHandler;
    double evaporationRate;
    double intensityFactor;
    // reward multiplier
    double alpha; // [0,1] defines relational rewarding between front ranks (large alpha --> elitism)
    vector<Solution> ants;
public:

    RBAS(Algorithm &algorithm, double evaporationRate, double intensityFactor, double alpha) :
            algorithm(&algorithm),
            modeHandler(&algorithm.rayHandler.getModeHandler()),
            evaporationRate(evaporationRate),
            intensityFactor(intensityFactor),
            alpha(alpha){}

    void run();

    void runBruteForce();

    void sendAnts();

    void updatePheromones(vector<Solution> &ants);

};