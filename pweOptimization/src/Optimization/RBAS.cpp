//
// Created by Christos on 6/19/2025.
//
#include "Optimization/RBAS.h"


#include <chrono>
#include <iostream>

void RBAS::run() {
    using namespace std::chrono;

    int& currentNumCycles = algorithm->currentNumCycles;
    int stagnationCounter = 0;
    while (currentNumCycles < algorithm->numGenerations + 1) {
        vector<Solution> ants;
        int i = 0;
        while (i < algorithm->genSize) {
            SystemState systemState = algorithm->rayHandler.propagate();
            if (systemState.getServiceRate() < 0.25) continue;

            ants.emplace_back(systemState);
            i++;
        }

        // Step 2: Fast non-dominated sorting
        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(ants);

        // Step 3: Crowding distance
        ParetoHandler::calculateCrowdingDistance(ants);

        // Step 4: Update Pareto Archive
        bool isUpdated = ParetoHandler::updateParetoArchive(algorithm->paretoArchive, firstFront);
        if (isUpdated) stagnationCounter++;

        // Step 5: Store result if required
        if (ParetoHandler::checkRepetitionMarks(algorithm->genSize * currentNumCycles, algorithm->genSize)) {
            algorithm->output[currentNumCycles] = algorithm->paretoArchive;
        }

        // Step 6 (Optional) : Apply Local Search
        if (algorithm->localSearch){

            if (static_cast<double>(currentNumCycles) / algorithm->numGenerations > 0.8) algorithm->numLocalSearches = 1;

            LocalSearch::applyLocalSearch(*algorithm);
            algorithm->localSearches.push_back(currentNumCycles);

        }

        if (stagnationCounter > 10){
            NSGAII nsga = NSGAII(*algorithm, 0.5,0.03);
            nsga.inputInitialPopulation(algorithm->paretoArchive);
            nsga.run();
        }

        // Step 7: Update pheromones
        updatePheromones(ants);

        currentNumCycles++;
    }
}


void RBAS::runBruteForce(){
    int currentNumCycles = 0;
    set<Solution> firstFront;
    while (currentNumCycles < algorithm->numGenerations){

        vector<Solution> ants;

        int i = 0;
        while (i < algorithm->genSize) {
            SystemState systemState = algorithm->rayHandler.propagate();
            if (systemState.getServiceRate() < 0.25) continue;

            ants.emplace_back(systemState);
            i++;
        }

        firstFront = ParetoHandler::fastNonDominatedSorting(ants);

        ParetoHandler::calculateCrowdingDistance(ants);

        ParetoHandler::updateParetoArchive(algorithm->paretoArchive, firstFront);

        if (ParetoHandler::checkRepetitionMarks(algorithm->genSize * currentNumCycles, algorithm->genSize)) {
            algorithm->output[algorithm->genSize * currentNumCycles] = algorithm->paretoArchive;
        }

        currentNumCycles++;



    }

}

void RBAS::updatePheromones(vector<Solution> &ants) {

    for (int i = 0; i < algorithm->graph->getNumTiles(); ++i){
        for (int j = 0; j < algorithm->graph->getNumModes(i); ++j){
            modeHandler->multiplyLikelihood(i, j, evaporationRate);
        }
    }
    double alpha = 0.5;
    for (auto &ant : ants){
        if (ant.getCrowdingDistance() == std::numeric_limits<double>::infinity()) ant.setCrowdingDistance(1);
        double pheromoneAmount = (exp(-alpha * ant.getFrontRank()) + ant.getCrowdingDistance());
        modeHandler->modifyModeLikelihood(ant.getModeList(),pheromoneAmount);
    }

    modeHandler->aliasMethod();




}