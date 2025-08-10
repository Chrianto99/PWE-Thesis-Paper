//
// Created by Christos on 8/7/2025.
//

#include "Solution.h"
#include "Propagation/RayHandler.h"
#include "Optimization/ParetoHandler.h"
#include "random"

#ifndef PWEOPTIMIZATION_LOCALSEARCH_H
#define PWEOPTIMIZATION_LOCALSEARCH_H

#endif //PWEOPTIMIZATION_LOCALSEARCH_H
class LocalSearch{
private:
        static Solution applyLocalSearch(Solution &solution, Graph& graph, int numSearches, int repetitionMark, int groupSize);
};