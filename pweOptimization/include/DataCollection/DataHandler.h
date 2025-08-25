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
#include "Optimization/HERA.h"

class DataHandler {

private:

    AlgorithmOutput data;
    double intensityFactor, evaporationRate, alpha;
    double mutationChance;
    double slope;
    int N;

public:

    DataHandler() = default;

    void setHERAParameters(double slope, double alpha, int N) {
        this->slope = slope;
        this->alpha = alpha;
        this->N = N;
    }

    void setMOACOParams(double intensityFactor, double evaporationRate, double alpha) {
        this->intensityFactor = intensityFactor;
        this->evaporationRate = evaporationRate;
        this->alpha = alpha;
    }

    void setNSGAParams(double mutationChance) {
        this->mutationChance = mutationChance;
    }


    AlgorithmOutput returnData(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels);

    map<int, vector<vector<double>>>
    createFronts(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels);

    void
    runSimulation(string algorithm, bool localSearch, int numTiles, int numUsers, int numGraphs, int numGenerations,
                  int numRepetitions, int roomDims[3]);


};
