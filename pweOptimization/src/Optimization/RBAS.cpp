//
// Created by Christos on 6/19/2025.
//
#include "Optimization/RBAS.h"
#include <chrono>
#include <iostream>

void RBAS::run() {
    using namespace std::chrono;

    int &currentNumCycles = algorithm->currentNumCycles;
    int stagnationCounter = 0;
    while (currentNumCycles < algorithm->numGenerations + 1) {

        // Step 1: Send ants to construct solutions
        vector<Solution> ants = sendAnts(algorithm->genSize);

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

//        if (stagnationCounter > 10) {
//            NSGAII nsga = NSGAII(*algorithm, 0.03);
//            nsga.inputInitialPopulation(algorithm->paretoArchive);
//            nsga.run();
//        }

        // Step 7: Update pheromones
        updatePheromones(ants);

        currentNumCycles++;
    }
}


void RBAS::runBruteForce() {
    int currentNumCycles = 0;
    set<Solution> firstFront;
    while (currentNumCycles < algorithm->numGenerations + 1) {

        vector<Solution> ants = sendAnts(algorithm->genSize);

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

    //Pheromone Evaporation
    for (int i = 0; i < algorithm->graph->getNumTiles(); ++i) {
        for (int j = 0; j < algorithm->graph->getNumModes(i); ++j) {
            modeHandler->scaleModeLikelihood(pair<int, int>(i, j), evaporationRate);
        }
    }
    //Pheromone reward (takes in to account both crowding distance and rank)
    for (auto &ant: ants) {

        if (ant.getCrowdingDistance() == std::numeric_limits<double>::infinity()) ant.setCrowdingDistance(1);

        double pheromoneAmount = intensityFactor * (exp(-alpha * ant.getFrontRank()) + ant.getCrowdingDistance());

        for (auto &pair: ant.getModeList()) modeHandler->increaseModeLikelihood(pair, pheromoneAmount);
    }

    modeHandler->aliasMethod();


}

vector<Solution> RBAS::sendAnts(int num) {

    vector<Solution> ants;
    int i = 0;
    while (i < num) {
        SystemState systemState = algorithm->rayHandler.propagate();
        if (systemState.getServiceRate() == 0) continue;

        ants.emplace_back(systemState);
        i++;
    }
    return ants;
}
