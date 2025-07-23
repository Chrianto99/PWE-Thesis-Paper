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
            if (systemState.getMinPower() == 0) continue;
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

    while (currentNumCycles < numCycles){

        vector<Solution> ants;

        int i = 0;
        while (i < numAntsPerCycle) {
            SystemState systemState = rayHandler.propagate();
            if (systemState.getMinPower() == 0) continue;
            ants.emplace_back(systemState);
            i++;
        }

        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(ants);

        ParetoHandler::calculateCrowdingDistance(ants);

        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, firstFront);

        if (ParetoHandler::checkRepetitionMarks(numAntsPerCycle * currentNumCycles, numAntsPerCycle)) {
            output[numAntsPerCycle * currentNumCycles] = paretoArchive;
        }

        currentNumCycles++;



    }

}

void RBAS::updatePheromones(vector<Solution> &ants) {

    double alpha = 1;
    for (auto &ant : ants){
        if (ant.getCrowdingDistance() == std::numeric_limits<double>::infinity()) ant.setCrowdingDistance(1);
        double pheromoneAmount = ant.getCrowdingDistance() * intensityFactor * exp(-alpha * ant.getFrontRank());
        modeHandler->modifyModeLikelihood(ant.getModeList(),pheromoneAmount);

    }

    modeHandler->aliasMethod();






}