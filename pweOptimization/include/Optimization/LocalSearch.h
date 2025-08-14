//
// Created by Christos on 8/7/2025.
//

#include "Solution.h"
#include "Propagation/RayHandler.h"
#include "Optimization/ParetoHandler.h"
#include "random"
#include "Algorithm.h"

#ifndef PWEOPTIMIZATION_LOCALSEARCH_H
#define PWEOPTIMIZATION_LOCALSEARCH_H

#endif //PWEOPTIMIZATION_LOCALSEARCH_H

#pragma once
class LocalSearch{
public:
        static void applyLocalSearch(Algorithm &algorithm);

        static void applyLocalSearch(Algorithm &algorithm, vector<Solution> &solutions);

        static Solution applyLocalSearchToSol(const Solution &solution, Algorithm &algorithm);
};