//
// Created by Christos on 3/18/2025.
//
#include <random>
#include "iostream"
#include "array"
#include "Graph/Graph.h"
#include "SystemState.h"
#include "random"
#include <chrono>
#ifndef PWEOPTIMIZATION_MODEMANAGER_H
#define PWEOPTIMIZATION_MODEMANAGER_H
using namespace std;

class ModeHandler {
private:
    Graph* graph;
    vector<vector<int>> tileDistributions;
    vector<vector<double>> probabilities;
    vector<vector<int>> aliases;
    std::mt19937 randGen;

public:

    ModeHandler() = default;

    ModeHandler(Graph &graph, int value)
            : graph(&graph), randGen(std::chrono::system_clock::now().time_since_epoch().count()){

        for (int i = 0; i < graph.getNumTiles() ; ++i) {
            std::vector<int> tileDist;
            for (int j = 0; j < graph.getNumModes(i) ; ++j) {
                tileDist.push_back(value);

            }
            tileDistributions.push_back(tileDist);
        }

        int numTiles = graph.getNumTiles();

        probabilities.resize(numTiles);
        aliases.resize(numTiles);

        for (int i = 0; i < numTiles; ++i) {
            int numModes = graph.getNumModes(i);

            // Resize the inner vectors directly (one-time allocation for each tile)
            probabilities[i].resize(numModes, 0.0);
            aliases[i].resize(numModes, 0);  // Initialize with 0

            // No need for the inner push_back calls anymore
        }

        aliasMethod();

    }

    [[nodiscard]] const std::vector<std::vector<int>>& getTileDistributions() const { return tileDistributions; }
    [[nodiscard]] const std::vector<std::vector<double>>& getProbabilities() const { return probabilities; }
    [[nodiscard]] const std::vector<std::vector<int>>& getAliases() const { return aliases; }
    [[nodiscard]] std::mt19937& getRandGen() { return randGen; } // Non-const (modifiable)

    void aliasMethod();

    int chooseMode(int tileId);

    void activateRandomModes(SystemState &systemState);

    void modifyModeLikelihood(vector<pair<int,int>> &modeList, double amount);







};


#endif //PWEOPTIMIZATION_MODEMANAGER_H
