//
// Created by Christos on 8/12/2025.
//
#include "Optimization/HERA.h"

void HERA::run() {
    using namespace std::chrono;

    int currentNumCycles = algorithm->numGenerations;
    int stagnationCounter = 0;

    while (currentNumCycles < algorithm->numGenerations + 1) {

        vector<Solution> solutions;
        int i = 0;
        while (i < algorithm->genSize) {
            SystemState systemState = algorithm->rayHandler.propagate();
            if (systemState.getServiceRate() == 0) continue;

            solutions.emplace_back(systemState);
            i++;
        }

        // Step 2: Fast non-dominated sorting
        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(solutions);

        // Step 3: Crowding distance
        ParetoHandler::calculateCrowdingDistance(solutions);

        // Step 4: Update Pareto Archive
        bool paretoUpdated = ParetoHandler::updateParetoArchive(algorithm->paretoArchive, firstFront);
        if (!paretoUpdated) stagnationCounter++;

        // Step 5: Store result if required
        if (ParetoHandler::checkRepetitionMarks(algorithm->genSize * currentNumCycles, algorithm->genSize)) {
            algorithm->output[algorithm->genSize * currentNumCycles] = algorithm->paretoArchive;
        }

        // Step 6: Update pheromones
        updateDistributions(solutions);

        currentNumCycles++;

    }
}


void HERA::updateDistributions(vector<Solution> &solutions) {

    double alpha = 0.5;
    for (auto &sol : solutions){
        if (sol.getCrowdingDistance() == std::numeric_limits<double>::infinity()) sol.setCrowdingDistance(1);
        double pheromoneAmount = intensityFactor * (exp(-alpha * sol.getFrontRank()) + sol.getCrowdingDistance());
        modeHandler->modifyModeLikelihood(sol.getModeList(),pheromoneAmount);
    }

    modeHandler->aliasMethod();


}
