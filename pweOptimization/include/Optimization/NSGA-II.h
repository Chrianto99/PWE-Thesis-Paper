//
// Created by Christos on 6/14/2025.
//

#ifndef PWEOPTIMIZATION_NSGA_II_H
#define PWEOPTIMIZATION_NSGA_II_H

#endif //PWEOPTIMIZATION_NSGA_II_H

#include "vector"
#include "set"
#include "list"
#include "unordered_set"
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Solution.h"
#include "Algorithm.h"
#include "LocalSearch.h"

#pragma once

using namespace std;

class NSGAII {
private:
    Algorithm *algorithm;
    int totalSolsCreated = 0;
    double mutationChance;
    vector<Solution> population;

public:

    NSGAII(Algorithm &algorithm, double mutationChance)
            : algorithm(&algorithm),
              mutationChance(mutationChance) {}

    void run();

    vector<Solution> createInitialPopulation();

    vector<Solution> inputInitialPopulation(set<Solution> &population);

    vector<Solution> generateOffspring();

    vector<Solution> selectNextGeneration();

    Solution &tournamentSelection();

    Solution crossover(const Solution &parent1, const Solution &parent2);

    Solution mutate(Solution &solution);

};

