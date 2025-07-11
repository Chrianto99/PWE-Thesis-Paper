//
// Created by Christos on 6/19/2025.
//

#ifndef PWEOPTIMIZATION_RBAS_H
#define PWEOPTIMIZATION_RBAS_H

#endif //PWEOPTIMIZATION_RBAS_H

#include "set"
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "ParetoHandler.h"
using namespace std;

class RBAS {

private:
    Graph *graph;
    RayHandler rayHandler;
    ModeHandler* modeHandler;
    int numAntsPerCycle;
    int numCycles;
    double evaporationRate;
    double intensityFactor;
    std::mt19937 randGen;
    set<Solution> paretoArchive;
    map<int,set<Solution>> output;


public:

    RBAS(Graph& graph, int numAntsPerCycle, int numCycles, double evaporationRate, double intensityFactor):
    graph(&graph),
    rayHandler(RayHandler(graph)),
    modeHandler(&rayHandler.getModeHandler()),
    numAntsPerCycle(numAntsPerCycle),
    evaporationRate(evaporationRate),
    intensityFactor(intensityFactor),
    numCycles(numCycles){}

    void run();

    void runBruteForce();

    void updatePheromones(vector<Solution> &ants);

    map<int,set<Solution>> &getOutput(){
        return output;
    }


};