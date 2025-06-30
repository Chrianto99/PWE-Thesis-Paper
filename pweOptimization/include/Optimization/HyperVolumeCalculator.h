//
// Created by Christos on 6/27/2025.
//

#ifndef PWEOPTIMIZATION_HYPERVOLUMECALCULATOR_H
#define PWEOPTIMIZATION_HYPERVOLUMECALCULATOR_H

#endif //PWEOPTIMIZATION_HYPERVOLUMECALCULATOR_H

#include "Solution.h"


class HyperVolumeCalculator{

public:

    vector<pair<double,double>> solutionsToPoints(vector<Solution> solutions);

    void calculateHyperVolume(vector<pair<double,double>> points, pair<double,double> refPoint);



};
