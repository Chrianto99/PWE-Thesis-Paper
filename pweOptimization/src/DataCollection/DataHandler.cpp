//
// Created by Christos on 7/12/2025.
//
#include "DataCollection/DataHandler.h"


AlgorithmOutput
DataHandler::returnData(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels) {

    data = AlgorithmOutput(output, objectiveLabels);

    createFronts(output, objectiveLabels);

    return data;

}

map<int, vector<vector<double>>>
DataHandler::createFronts(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels) {
    map<int, vector<vector<double>>> extractedFronts;

    for (const auto &[repMark, solutions]: output) {

        vector<vector<double>> front;
        for (const auto &sol: solutions) {

            vector<double> point;
            for (auto &label: objectiveLabels) {
                point.push_back(sol.getObjectives().at(label));
            }
            front.push_back(point);

        }
        extractedFronts[repMark] = front;

    }

    data.setFronts(extractedFronts);

    return extractedFronts;
}

void DataHandler::runSimulation(string algorithm, bool localSearch, int numTiles, int numUsers, int numGraphs, int numGenerations,
                                int numRepetitions, int *roomDims) {
    auto* g = new Graph();

    string roomPath = "Graphs_" + to_string(roomDims[0]) + "x" + to_string(roomDims[1])
                      + "x" + to_string(roomDims[2]);

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

            Algorithm alg = Algorithm(*g,numTiles * 1.5, numGenerations, localSearch);

            if (algorithm == "NSGAII") {
                NSGAII nsgaii = NSGAII(alg, mutationChance);
                nsgaii.run();
                ParetoHandler::mergeOutputs(currentOutput, alg.output);
            }
            else if (algorithm == "RBAS"){
                RBAS rbas = RBAS(alg, evaporationRate, intensityFactor, alpha);
                rbas.run();
                ParetoHandler::mergeOutputs(currentOutput, alg.output);
            }
            else if (algorithm == "BruteForce"){
                RBAS rbas = RBAS(alg, 0, 0, 0);
                rbas.runBruteForce();
                ParetoHandler::mergeOutputs(currentOutput, alg.output);

            }
            else if (algorithm == "HERA"){
                HERA hera = HERA(alg, alpha, slope, N);
                hera.run();
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

        data = dataHandler.returnData(convertedOutput,
                                                      vector<string>{"averageDelaySpread", "averagePower"});
        string writePath;
        if (localSearch) writePath = roomPath + "/results/" + algorithm + "-NSGAII-LS";

        else writePath = roomPath + "/results/" + algorithm;

        data.writeToJson(writePath, graphID, numTiles, numUsers);
    }


}


