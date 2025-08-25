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
private:
    Algorithm* algorithm;
    ModeHandler* modeHandler;
    double slope, alpha;
    int N;

public:
    HERA(Algorithm& algorithm,double alpha, double slope, int N):
    algorithm(&algorithm),
    modeHandler(&algorithm.rayHandler.getModeHandler()),
    alpha(alpha),
    slope(slope),
    N(N)
    {}


    void run();

    void exploitationPhase();

    vector<Solution> sendSwarm(int num);

    void updateDistributions(vector<Solution> &solution);


};