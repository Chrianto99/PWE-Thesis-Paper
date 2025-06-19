//
// Created by Christos on 6/14/2025.
//

#ifndef PWEOPTIMIZATION_NSGA_II_H
#define PWEOPTIMIZATION_NSGA_II_H

#endif //PWEOPTIMIZATION_NSGA_II_H
#include "vector"
#include "list"
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Solution.h"

using namespace std;

class NSGAII{
private:

    Graph* graph;
    RayHandler rayHandler;
    int populationSize;
    int numGenerations ,genCount = 0, totalSolsCreated = 0;
    double crossoverChance;
    double mutationChance;
    std::mt19937 randGen;
    vector<Solution> paretoArchive;

public:

    NSGAII(Graph& graph, int populationSize, int numGenerations, double crossoverChance, double mutationChance)
            : graph(&graph),
              populationSize(populationSize),
              numGenerations(numGenerations),
              crossoverChance(crossoverChance),
              mutationChance(mutationChance),
              rayHandler(RayHandler(graph)) // initialize with new
    {}

    void run();

    vector<Solution> createInitialPopulation();

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

