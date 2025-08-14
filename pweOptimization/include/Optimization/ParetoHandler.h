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

#pragma once

using namespace std;

class ParetoHandler {

public:

    //Performs fast non dominated sorting (FNDS) in a set of solutions
    //Assigns the rank to solution and returns just the highest ranked front
    static set<Solution> fastNonDominatedSorting(vector<Solution> &solutions);

    //Only does FNDS for the best front
    static set<Solution> getFirstFront(vector<Solution>& solutions);

    //Updates Pareto Archive given previous Archive and a new set of solutions
    static bool updateParetoArchive(set<Solution> &paretoArchive, set<Solution> &newSolutions);

    //Calculates Crowding Distance
    static void calculateCrowdingDistance(vector<Solution> &solutions);

    //Checks Pareto Dominance for multiple objectives (can be used for more than 2 objectives)
    static bool dominates(const Solution &a, const Solution &b);

    //Logic for when so save algorithm results
    static bool checkRepetitionMarks(int currentRepMark, int groupSize);

    //Extracts unified outputs(Fronts) for multiple runs of a single algorithm
    static void mergeOutputs(map<int, set<Solution>> &oldArchive, map<int, set<Solution>> &newArchive);

    //static void updatePopulation(set<Solution> &paretoArchive, int maxNumber);

};