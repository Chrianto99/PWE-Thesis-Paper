//
// Created by Christos on 8/7/2025.
//
#include "Optimization/LocalSearch.h"


Solution LocalSearch::applyLocalSearch(Solution &solution, Graph& graph, int numSearches, int repetitionMark, int groupSize){
    RayHandler rayHandler = RayHandler(graph);
    random_device rd;
    mt19937 randGen(rd());
    vector<pair<int,int>> modeList = solution.getModeList();

    std::vector<int> indices(modeList.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), randGen);

    int numSearchesDone = 0;
    for (int r : indices){

        int tileId = modeList[r].first;
        int originalMode = modeList[r].second;

        for (int modeId = 0; modeId < graph.getNumModes(tileId); modeId++){

            if (modeId == originalMode) continue;

            modeList[r].second = modeId;
            SystemState systemState = rayHandler.propagateGivenModes(modeList);
            Solution newSol = Solution(systemState);
            ParetoHandler::checkRepetitionMarks(repetitionMark + numSearchesDone, groupSize);
            numSearchesDone++;
            modeList[r].second = originalMode;

            if (ParetoHandler::dominates(newSol,solution)) solution = std::move(newSol);
            if (numSearchesDone >= numSearches) return solution;


        }


    }





}