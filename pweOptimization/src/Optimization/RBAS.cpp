//
// Created by Christos on 6/19/2025.
//
#include "Optimization/RBAS.h"


void RBAS::run(){
    int currentNumCycles = 0;

    while (currentNumCycles < numCycles){

        cout << currentNumCycles << endl;
        vector<Solution> ants;

        for (int i = 0; i < numAntsPerCycle; ++i) {
            SystemState systemState = rayHandler.propagate();
            Solution ant = Solution(systemState);
            ants.push_back(ant);
        }

        ParetoHandler::fastNonDominatedSorting(ants);
        ParetoHandler::calculateCrowdingDistance(ants);
        ParetoHandler::updateParetoArchive(paretoArchive, ants , 200);

        updatePheromones(ants);
        currentNumCycles++;



    }

}

void RBAS::updatePheromones(vector<Solution> &ants) {

    double alpha = 1;
    for (auto &ant : ants){

        double pheromoneAmount = intensityFactor * exp(-alpha * ant.getFrontRank());
        modeHandler->modifyModeLikelihood(ant.getModeList(),pheromoneAmount);

    }

    modeHandler->aliasMethod();






}