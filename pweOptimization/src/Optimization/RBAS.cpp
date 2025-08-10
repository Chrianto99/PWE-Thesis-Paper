//
// Created by Christos on 6/19/2025.
//
#include "Optimization/RBAS.h"


#include <chrono>
#include <iostream>

void RBAS::run() {
    using namespace std::chrono;

    int currentNumCycles = 0;

    while (currentNumCycles < numCycles + 1) {


        vector<Solution> ants;
        int i = 0;
        while (i < numAntsPerCycle) {
            SystemState systemState = rayHandler.propagate();
            if (systemState.getServiceRate() < 0.25) continue;

            ants.emplace_back(systemState);
            i++;
        }

        // Step 2: Fast non-dominated sorting
        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(ants);

        // Step 3: Crowding distance
        ParetoHandler::calculateCrowdingDistance(ants);

        // Step 4: Update Pareto Archive
        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, firstFront);

        // Step 5: Store result if required
        if (ParetoHandler::checkRepetitionMarks(numAntsPerCycle * currentNumCycles, numAntsPerCycle)) {
            output[numAntsPerCycle * currentNumCycles] = paretoArchive;
        }

        // Step 6: Update pheromones
        updatePheromones(ants);

        currentNumCycles++;
    }
}


void RBAS::runBruteForce(){
    int currentNumCycles = 0;
    set<Solution> firstFront;
    while (currentNumCycles < numCycles){

        vector<Solution> ants;

        int i = 0;
        while (i < numAntsPerCycle) {
            SystemState systemState = rayHandler.propagate();
            if (systemState.getServiceRate() < 0.25) continue;

            ants.emplace_back(systemState);
            i++;
        }

        firstFront = ParetoHandler::fastNonDominatedSorting(ants);

        ParetoHandler::calculateCrowdingDistance(ants);

        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, firstFront);

        if (ParetoHandler::checkRepetitionMarks(numAntsPerCycle * currentNumCycles, numAntsPerCycle)) {
            output[numAntsPerCycle * currentNumCycles] = paretoArchive;
        }

        currentNumCycles++;



    }

}

void RBAS::updatePheromones(vector<Solution> &ants) {

    for (int i = 0; i < graph->getNumTiles(); ++i){
        for (int j = 0; j < graph->getNumModes(i); ++j){
            modeHandler->multiplyLikelihood(i, j, evaporationRate);
        }
    }
    double alpha = 0.5;
    for (auto &ant : ants){
        if (ant.getCrowdingDistance() == std::numeric_limits<double>::infinity()) ant.setCrowdingDistance(1);
        double pheromoneAmount = intensityFactor * (exp(-alpha * ant.getFrontRank()) + ant.getCrowdingDistance());
        modeHandler->modifyModeLikelihood(ant.getModeList(),pheromoneAmount);
    }

    modeHandler->aliasMethod();




}