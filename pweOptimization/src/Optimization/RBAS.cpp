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

        auto t_start = high_resolution_clock::now();
        auto t_end = high_resolution_clock::now();

        // Step 1: Generate ants
        t_start = high_resolution_clock::now();
        vector<Solution> ants;
        int i = 0;
        while (i < numAntsPerCycle) {
            SystemState systemState = rayHandler.propagate();
            if (systemState.getMinPower() == 0) continue;
            ants.emplace_back(systemState);
            i++;
        }
        t_end = high_resolution_clock::now();
        std::cout << "[TIMER] generateAnts: " << duration_cast<microseconds>(t_end - t_start).count() << " μs\n";

        // Step 2: Fast non-dominated sorting
        t_start = high_resolution_clock::now();
        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(ants);
        t_end = high_resolution_clock::now();
        std::cout << "[TIMER] fastNonDominatedSorting: " << duration_cast<microseconds>(t_end - t_start).count() << " μs\n";

        // Step 3: Crowding distance
        t_start = high_resolution_clock::now();
        ParetoHandler::calculateCrowdingDistance(ants);
        t_end = high_resolution_clock::now();
        std::cout << "[TIMER] calculateCrowdingDistance: " << duration_cast<microseconds>(t_end - t_start).count() << " μs\n";

        // Step 4: Update Pareto Archive
        t_start = high_resolution_clock::now();
        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, firstFront);
        t_end = high_resolution_clock::now();
        std::cout << "[TIMER] updateParetoArchive: " << duration_cast<microseconds>(t_end - t_start).count() << " μs\n";

        // Step 5: Store result if required
        t_start = high_resolution_clock::now();
        if (ParetoHandler::checkRepetitionMarks(numAntsPerCycle * currentNumCycles, numAntsPerCycle)) {
            output[numAntsPerCycle * currentNumCycles] = paretoArchive;
        }
        t_end = high_resolution_clock::now();
        std::cout << "[TIMER] checkRepetitionMarks + output store: " << duration_cast<microseconds>(t_end - t_start).count() << " μs\n";

        // Step 6: Update pheromones
        t_start = high_resolution_clock::now();
        updatePheromones(ants);
        t_end = high_resolution_clock::now();
        std::cout << "[TIMER] updatePheromones: " << duration_cast<microseconds>(t_end - t_start).count() << " μs\n";

        currentNumCycles++;
    }
}


//void RBAS::runBruteForce(){
//    int currentNumCycles = 0;
//
//    while (currentNumCycles < numCycles){
//
//        vector<Solution> ants;
//
//        for (int i = 0; i < numAntsPerCycle; ++i) {
//            SystemState systemState = rayHandler.propagate();
//            Solution ant = Solution(systemState);
//            ants.push_back(ant);
//        }
//
//        ParetoHandler::fastNonDominatedSorting(ants);
//        ParetoHandler::calculateCrowdingDistance(ants);
//        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, ants , 200);
//
//        if (ParetoHandler::checkRepetitionMarks(numAntsPerCycle * currentNumCycles, numAntsPerCycle)){
//            output[numAntsPerCycle * currentNumCycles] = paretoArchive;
//        }
//
//        currentNumCycles++;
//
//
//
//    }
//
//}

void RBAS::updatePheromones(vector<Solution> &ants) {

    double alpha = 1;
    for (auto &ant : ants){
        if (ant.getCrowdingDistance() == std::numeric_limits<double>::infinity()) ant.setCrowdingDistance(1);
        double pheromoneAmount = ant.getCrowdingDistance() * intensityFactor * exp(-alpha * ant.getFrontRank());
        modeHandler->modifyModeLikelihood(ant.getModeList(),pheromoneAmount);

    }

    modeHandler->aliasMethod();






}