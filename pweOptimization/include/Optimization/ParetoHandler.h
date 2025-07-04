//
// Created by Christos on 6/14/2025.
//

#ifndef PWEOPTIMIZATION_PARETOHANDLER_H
#define PWEOPTIMIZATION_PARETOHANDLER_H

#endif //PWEOPTIMIZATION_PARETOHANDLER_H

#include "vector"
#include <limits>
#include "Solution.h"
#include "unordered_map"
#include "map"
using namespace std;

class ParetoHandler {


public:

    static void fastNonDominatedSorting(vector<Solution> &solutions);

    static vector<Solution>
    updateParetoArchive(vector<Solution> &paretoArchive, vector<Solution> &newSolutions, int maxCapacity);

    static void calculateCrowdingDistance(vector<Solution> &solutions);

    static bool dominates(const Solution &a, const Solution &b);

    static bool equals(const Solution &a, const Solution &b);

    static bool checkRepetitionMarks(int currentRepMark);

    static map<int, vector<Solution>>
    mergeOutputs(map<int, vector<Solution>> &oldArchive, map<int, vector<Solution>> &newArchive);

};