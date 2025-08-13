//
// Created by Christos on 8/11/2025.
//

#ifndef PWEOPTIMIZATION_ALGORITHM_H
#define PWEOPTIMIZATION_ALGORITHM_H

#endif //PWEOPTIMIZATION_ALGORITHM_H

#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Solution.h"
#include "set"

#pragma once

class Algorithm {

public:

    Graph *graph;
    RayHandler rayHandler;
    int genSize, numGenerations;
    int currentNumCycles;

    std::mt19937 randGen;
    set<Solution> paretoArchive;
    map<int, set<Solution>> output;

    bool localSearch;
    int numLocalSearches;
    vector<int> localSearches;

    Algorithm(Graph &graph, int genSize, int numGenerations, bool localSearch) :
            graph(&graph),
            rayHandler(RayHandler(graph)),
            genSize(genSize),
            numGenerations(numGenerations),
            localSearch(localSearch) {
        currentNumCycles = 0;
        numLocalSearches = 0;
    }

};
