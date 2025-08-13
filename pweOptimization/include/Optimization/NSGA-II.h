//
// Created by Christos on 6/14/2025.
//

#ifndef PWEOPTIMIZATION_NSGA_II_H
#define PWEOPTIMIZATION_NSGA_II_H

#endif //PWEOPTIMIZATION_NSGA_II_H
#include "vector"
#include "set"
#include "list"
#include "unordered_set"
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Solution.h"
#include "Algorithm.h"
#include "LocalSearch.h"
#pragma once

using namespace std;

class NSGAII{
private:
    Algorithm* algorithm;
    int totalSolsCreated = 0;
    double crossoverChance;
    double mutationChance;
    vector<Solution> population;




public:

    NSGAII(Algorithm& algorithm, double crossoverChance, double mutationChance)
            : algorithm(&algorithm),
              crossoverChance(crossoverChance),
              mutationChance(mutationChance){}

    void run();

    vector<Solution> createInitialPopulation();

    vector<Solution> inputInitialPopulation(set<Solution> &population);

    vector<Solution> generateOffspring(vector<Solution> &population);

    Solution crossover(const Solution &parent1,const Solution &parent2);

    Solution& tournamentSelection(const std::vector<Solution>& population);

    Solution mutate(Solution &solution);

    vector<Solution> selectNextGeneration(vector<Solution>& population);

    Graph *getGraph() const;

    void setGraph(Graph *graph);

    const RayHandler &getRayHandler() const;

    void setRayHandler(const RayHandler &rayHandler);

    int getPopulationSize() const;

    void setPopulationSize(int populationSize);

    int getNumGenerations() const;

    void setNumGenerations(int numGenerations);

    int getGenCount() const;

    void setGenCount(int genCount);

    int getTotalSolsCreated() const;

    void setTotalSolsCreated(int totalSolsCreated);

    double getCrossoverChance() const;

    void setCrossoverChance(double crossoverChance);

    double getMutationChance() const;

    void setMutationChance(double mutationChance);

    const mt19937 &getRandGen() const;

    void setRandGen(const mt19937 &randGen);

    const vector<Solution> &getParetoArchive() const;

    void setParetoArchive(const vector<Solution> &paretoArchive);



};

