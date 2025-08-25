//
// Created by Christos on 8/12/2025.
//
#include "Optimization/HERA.h"



void HERA::run() {
    using namespace std::chrono;

    int &currentNumCycles = algorithm->currentNumCycles;
    int stagnationCounter = 0;

    while (currentNumCycles < algorithm->numGenerations + 1) {

        if (stagnationCounter > 5){
            exploitationPhase();
            stagnationCounter -= 5;
        }

        vector<Solution> solutions = sendSwarm(algorithm->genSize);

        // Step 2: Fast non-dominated sorting
        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(solutions);

        // Step 3: Crowding distance
        ParetoHandler::calculateCrowdingDistance(solutions);

        // Step 4: Update Pareto Archive
        bool paretoUpdated = ParetoHandler::updateParetoArchive(algorithm->paretoArchive, firstFront);
        if (!paretoUpdated) stagnationCounter++;

        // Step 5: Store result if required
        if (ParetoHandler::checkRepetitionMarks(algorithm->genSize * currentNumCycles, algorithm->genSize)) {
            algorithm->output[currentNumCycles] = algorithm->paretoArchive;
        }

        // Step 6: Update pheromones
        updateDistributions(solutions);


        currentNumCycles++;

    }
}

void HERA::exploitationPhase() {

    algorithm->numLocalSearches += 1;
    LocalSearch::applyLocalSearch(*algorithm);

    slope *= 2;
    vector<Solution> pav(algorithm->paretoArchive.begin(), algorithm->paretoArchive.end());
    ParetoHandler::fastNonDominatedSorting(pav);
    ParetoHandler::calculateCrowdingDistance(pav);
    updateDistributions(pav);

    vector<Solution> solutions = sendSwarm(N);

    set<Solution> firstFront = ParetoHandler::getFirstFront(solutions);
    ParetoHandler::updateParetoArchive(algorithm->paretoArchive, firstFront);


}


void HERA::updateDistributions(vector<Solution> &solutions) {

    for (auto &sol: solutions) {
        if (sol.getCrowdingDistance() == std::numeric_limits<double>::infinity()) sol.setCrowdingDistance(1);
        double pheromoneAmount = slope * (exp(-alpha * sol.getFrontRank()) + sol.getCrowdingDistance());
        modeHandler->modifyModeLikelihood(sol.getModeList(), pheromoneAmount);
    }

    modeHandler->aliasMethod();


}

vector<Solution> HERA::sendSwarm(int num) {

    vector<Solution> solutions;
    int i = 0;
    while (i < num) {
        SystemState systemState = algorithm->rayHandler.propagate();
        if (systemState.getServiceRate() == 0) continue;

        solutions.emplace_back(systemState);
        i++;
    }
    return solutions;
}
