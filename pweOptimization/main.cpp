#include <iostream>
#include <fstream>
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Optimization/NSGA-II.h"
#include "Optimization/RBAS.h"
#include "Optimization/Algorithm.h"
#include "DataCollection/DataHandler.h"
#include <chrono>



#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {

    Graph* g = new Graph();
    int numTiles = 32;
    int numUsers = 4;
    int numModes  = 0;
    int numGraphs = 100;

    int groupSize = numTiles * 1.5;
    int numGenerations = 50;
    int numRepetitions = 100;
    int roomDims[3] = {10, 6, 4};


    string roomPath = "Graphs_" + to_string(roomDims[0]) + "x" + to_string(roomDims[1])
                     + "x" + to_string(roomDims[2]);

    string algorithm = "RBAS";
    bool localSearch = true;

    for (int graphID = 0; graphID < numGraphs; graphID++) {

        cout << "graph:" << graphID << endl;
        string graphPath = roomPath + "/Rx_" + to_string(numUsers) +
                      "/Tiles_" + to_string(numTiles) +
                      "/Graph_" + to_string(graphID) + ".json";

        g->loadGraph(graphPath, *g);

        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(end - start);
        auto durationPerPropagation = duration.count() / 100;

        start = std::chrono::high_resolution_clock::now();
        map<int, set<Solution>> currentOutput;

        for (int i = 0; i < numRepetitions; ++i) {

            Algorithm alg = Algorithm(*g,groupSize, numGenerations, localSearch);

            if (algorithm == "NSGAII") {
                NSGAII nsgaii = NSGAII(alg, 0.03);
                nsgaii.run();
                ParetoHandler::mergeOutputs(currentOutput, alg.output);
            }
            else if (algorithm == "RBAS"){
                RBAS rbas = RBAS(alg, 0.8, 1, 0.5);
                rbas.run();
                ParetoHandler::mergeOutputs(currentOutput, alg.output);
            }
            else if (algorithm == "BruteForce"){
                RBAS rbas = RBAS(alg, 0.8, 1, 0.5);
                rbas.runBruteForce();
                ParetoHandler::mergeOutputs(currentOutput, alg.output);

            }


        }
        end = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(end - start);
        durationPerPropagation = duration.count() / numRepetitions;
        cout << "Time taken: " << durationPerPropagation << " ms" << endl;

        DataHandler dataHandler = DataHandler();

        map<int, vector<Solution>> convertedOutput;

        for (const auto &[key, solutionSet]: currentOutput) {
            // Convert each set to a vector
            convertedOutput[key] = vector<Solution>(solutionSet.begin(), solutionSet.end());
        }

        AlgorithmOutput data = dataHandler.returnData(convertedOutput,
                                                      vector<string>{"averageDelaySpread", "averagePower"});
        string writePath;
        if (localSearch) writePath = roomPath + "/results/" + algorithm + "-NSGAII-LS";

        else writePath = roomPath + "/results/" + algorithm;

        data.writeToJson(writePath, graphID, numTiles, numUsers);
    }


    if (true) cout << "";


}
