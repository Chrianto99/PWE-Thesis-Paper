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
    map<int,set<Solution>> output;

    bool localSearch;
    int numLocalSearches;
    vector<int> localSearches;

    Algorithm(Graph &graph, int genSize, int numGenerations, bool localSearch) :
        graph(&graph),
        rayHandler(RayHandler(graph)),
        genSize(genSize),
        numGenerations(numGenerations),
        localSearch(localSearch){
        currentNumCycles = 0;
        numLocalSearches = 0;
    }

    Graph *getGraph() const {
        return graph;
    }


    const RayHandler &getRayHandler() const {
        return rayHandler;
    }


    int getGenSize() const {
        return genSize;
    }

    int getNumGenerations() const {
        return numGenerations;
    }



    const mt19937 &getRandGen() const {
        return randGen;
    }

    const set<Solution> &getParetoArchive() const {
        return paretoArchive;
    }

    const map<int, set<Solution>> &getOutput() const {
        return output;
    }

    void setOutput(const map<int, set<Solution>> &output) {
        Algorithm::output = output;
    }

    bool isLocalSearch() const {
        return localSearch;
    }

    void setLocalSearch(bool localSearch) {
        Algorithm::localSearch = localSearch;
    }

    int getNumLocalSearches() const {
        return numLocalSearches;
    }

    void setNumLocalSearches(int numLocalSearches) {
        Algorithm::numLocalSearches = numLocalSearches;
    }

    const vector<int> &getLocalSearches() const {
        return localSearches;
    }

    void setLocalSearches(const vector<int> &localSearches) {
        Algorithm::localSearches = localSearches;
    }



};
