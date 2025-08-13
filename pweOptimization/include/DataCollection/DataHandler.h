//
// Created by Christos on 7/12/2025.
//

#ifndef PWEOPTIMIZATION_DATAHANDLER_H
#define PWEOPTIMIZATION_DATAHANDLER_H

#endif //PWEOPTIMIZATION_DATAHANDLER_H

#include "Optimization/Solution.h"
#include "AlgorithmOutput.h"
#include "set"

class DataHandler {

private:

    AlgorithmOutput data;

public:

    DataHandler() = default;

    AlgorithmOutput returnData(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels);

    map<int, vector<vector<double>>>
    createFronts(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels);

    void calculateHyperVolumes(const map<int, vector<vector<double>>> &fronts);

    vector<double> computeReferencePoint(const map<int, vector<vector<double>>> &fronts, double epsilon);


};
