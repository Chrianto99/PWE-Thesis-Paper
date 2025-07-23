#include <iostream>
#include <fstream>
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Optimization/NSGA-II.h"
#include "Optimization/RBAS.h"
#include "DataCollection/DataHandler.h"
#include <chrono>



#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {

    Graph* g = new Graph();
    int numTiles = 16;
    int numUsers = 4;
    int numModes  = 0;
    int numGraphs = 100;

    int numGenerations = numTiles * 1.5;
    int numCycles = 50;
    int numRepetitions = 100;


    for (int graphID = 0; graphID < numGraphs; graphID++) {

        string path = "Graphs_15x10x5/Rx_" + to_string(numUsers) +
                      "/Tiles_" + to_string(numTiles) +
                      "/Graph_" + to_string(graphID) + ".json";

        g->loadGraph(path, *g);


        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(end - start);
        auto durationPerPropagation = duration.count() / 100;

        start = std::chrono::high_resolution_clock::now();
        map<int, set<Solution>> currentOutput;

        for (int i = 0; i < numRepetitions; ++i) {
            //cout << i << endl;
            NSGAII alg = NSGAII(*g, 24, 100, 0.5, 0.02);
            alg.run();
            map<int, set<Solution>> output = ParetoHandler::mergeOutputs(currentOutput, alg.getOutput());
            currentOutput = output;
        }
        end = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(end - start);
        durationPerPropagation = duration.count() / 100;
        cout << "Time taken: " << durationPerPropagation << " ms" << endl;

        DataHandler dataHandler = DataHandler();

        map<int, vector<Solution>> convertedOutput;

        for (const auto &[key, solutionSet]: currentOutput) {
            // Convert each set to a vector
            convertedOutput[key] = vector<Solution>(solutionSet.begin(), solutionSet.end());
        }

        AlgorithmOutput data = dataHandler.returnData(convertedOutput,
                                                      vector<string>{"averageDelaySpread", "averagePower"});

        data.writeToJson("NSGAII", graphID, numTiles, numUsers);
    }


    if (true) cout << "";


}
