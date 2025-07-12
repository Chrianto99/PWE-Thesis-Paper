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
#include "set"
using namespace std;

class ParetoHandler {


public:

    static set<Solution> fastNonDominatedSorting(vector<Solution> &solutions);

    static set<Solution> getFirstFront(vector<Solution>& solutions);

    static set<Solution> updateParetoArchive(set<Solution> &paretoArchive, set<Solution> &newSolutions);

    static void calculateCrowdingDistance(vector<Solution> &solutions);

    static bool dominates(const Solution &a, const Solution &b);

    static bool equals(const Solution &a, const Solution &b);

    static bool checkRepetitionMarks(int currentRepMark, int groupSize);

    static map<int, set<Solution>> mergeOutputs(map<int, set<Solution>> &oldArchive, map<int, set<Solution>> &newArchive);

};