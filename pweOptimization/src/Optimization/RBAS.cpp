//
// Created by Christos on 6/19/2025.
//
#include "Optimization/RBAS.h"


void RBAS::run(){
    int currentNumCycles = 0;

    while (currentNumCycles < numCycles){

        vector<Solution> ants;
        int i = 0;
        while (i < numAntsPerCycle){
            SystemState systemState = rayHandler.propagate();
            Solution ant = Solution(systemState);
            ants.push_back(ant);
            i++;
        }

        ParetoHandler::fastNonDominatedSorting(ants);
        ParetoHandler::calculateCrowdingDistance(ants);
        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, ants , 200);
        vector<Solution> par = paretoArchive;

        if (ParetoHandler::checkRepetitionMarks(numAntsPerCycle * currentNumCycles)){
            output[numAntsPerCycle * currentNumCycles] = paretoArchive;
        }

        updatePheromones(ants);
        currentNumCycles++;

    }

}

void RBAS::runBruteForce(){
    int currentNumCycles = 0;

    while (currentNumCycles < numCycles){

        vector<Solution> ants;

        for (int i = 0; i < numAntsPerCycle; ++i) {
            SystemState systemState = rayHandler.propagate();
            Solution ant = Solution(systemState);
            ants.push_back(ant);
        }

        ParetoHandler::fastNonDominatedSorting(ants);
        ParetoHandler::calculateCrowdingDistance(ants);
        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, ants , 200);

        if (ParetoHandler::checkRepetitionMarks(numAntsPerCycle * currentNumCycles)){
            output[numAntsPerCycle * currentNumCycles] = paretoArchive;
        }

        currentNumCycles++;



    }

}

void RBAS::updatePheromones(vector<Solution> &ants) {

    double alpha = 1;
    for (auto &ant : ants){
        if (ant.getCrowdingDistance() == std::numeric_limits<double>::infinity()) ant.setCrowdingDistance(1);
        double pheromoneAmount = intensityFactor * exp(-alpha * ant.getFrontRank());
        modeHandler->modifyModeLikelihood(ant.getModeList(),pheromoneAmount);

    }

    modeHandler->aliasMethod();






}