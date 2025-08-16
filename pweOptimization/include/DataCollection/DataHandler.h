//
// Created by Christos on 7/12/2025.
//

#ifndef PWEOPTIMIZATION_DATAHANDLER_H
#define PWEOPTIMIZATION_DATAHANDLER_H

#endif //PWEOPTIMIZATION_DATAHANDLER_H

#include "Optimization/Solution.h"
#include "AlgorithmOutput.h"
#include "set"
#include "Optimization/Algorithm.h"
#include "Optimization/RBAS.h"
#include "Optimization/NSGA-II.h"

class DataHandler {

private:

    AlgorithmOutput data;

public:

    DataHandler() = default;

    AlgorithmOutput returnData(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels);

    map<int, vector<vector<double>>>
    createFronts(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels);

    void runSimulation(string algorithm, double intensityFactor, double evaporationRate, double alpha, bool localSearch, int numTiles, int numUsers, int numGraphs, int numGenerations, int numRepetitions ,int roomDims[3]);



};
