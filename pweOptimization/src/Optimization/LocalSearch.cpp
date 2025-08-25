//
// Created by Christos on 8/7/2025.
//
#include "Optimization/LocalSearch.h"


void LocalSearch::applyLocalSearch(Algorithm &algorithm) {
    int numLocalSearchesDone = 0;
    auto &paretoArchive = algorithm.paretoArchive;

    for (auto it = paretoArchive.begin();
         it != paretoArchive.end() && numLocalSearchesDone < algorithm.numLocalSearches; ) {

        // If already processed, skip to next
        if (it->localSearchApplied) {
            ++it;
            continue;
        }

        Solution improved = applyLocalSearchToSol(*it, algorithm);
        numLocalSearchesDone++;

        if (improved == *it) {

            ++it; // no change, move to next
        } else {
            it = paretoArchive.erase(it);    // erase returns the next iterator
            paretoArchive.insert(improved);  // insert result (we skip iterating over it immediately)
        }
    }
}

void LocalSearch::applyLocalSearch(Algorithm &algorithm, std::vector<Solution> &solutions) {
    int numLocalSearchesDone = 0;

    for (size_t i = 0; i < solutions.size() && numLocalSearchesDone < algorithm.numLocalSearches; ++i) {
        Solution &current = solutions[i];

        if (current.localSearchApplied) continue;

        Solution improved = applyLocalSearchToSol(current, algorithm);
        numLocalSearchesDone++;

        if (improved != current) {
            // Replace in place
            solutions[i] = std::move(improved);
            // Optionally decrement i if you want to reprocess the new solution
            // i--;
        }
    }
}

Solution LocalSearch::applyLocalSearchToSol(const Solution &solution, Algorithm &algorithm) {
    // Initialize RNG once per call
    static thread_local std::mt19937 randGen(std::random_device{}());

    // Copy and shuffle indices for random order
    std::vector<int> indices(solution.getModeList().size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), randGen);

    Solution bestSolution = solution;
    bestSolution.localSearchApplied = true;

    auto modeList = solution.getModeList(); // local copy to modify

    for (int r : indices) {
        int tileId = modeList[r].first;
        int originalMode = modeList[r].second;

        for (int modeId = 0; modeId < algorithm.graph->getNumModes(tileId); ++modeId) {
            if (modeId == originalMode) continue;

            // Try new mode
            modeList[r].second = modeId;
            SystemState systemState = algorithm.rayHandler.propagateGivenModes(modeList);
            Solution newSol(systemState);

            // Restore original mode
            modeList[r].second = originalMode;

            // If new solution dominates, store it
            if (ParetoHandler::dominates(newSol, solution)) {
                bestSolution = std::move(newSol);
                return bestSolution;
            }
        }
    }

    // done:

    return bestSolution;
}

