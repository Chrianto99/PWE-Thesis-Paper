//
// Created by Christos on 8/12/2025.
//

#ifndef PWEOPTIMIZATION_HERA_H
#define PWEOPTIMIZATION_HERA_H

#endif //PWEOPTIMIZATION_HERA_H

#include "Algorithm.h"
#include "Propagation/ModeHandler.h"
#include "ParetoHandler.h"
#include "LocalSearch.h"

class HERA{

    Algorithm* algorithm;
    ModeHandler* modeHandler;
    double intensityFactor;

    HERA(Algorithm& algorithm, double intensityFactor):
    algorithm(&algorithm),
    modeHandler(&algorithm.rayHandler.getModeHandler()),
    intensityFactor(intensityFactor){}

    void run();

    void updateDistributions(vector<Solution> &solutions);


};