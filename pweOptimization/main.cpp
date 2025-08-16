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

    struct SimulationConfig {
        int numTiles;
        int numUsers;
        int numGraphs;

        int groupSize;
        int numGenerations;
        int numRepetitions;

        int roomDims[3];
        bool localSearch;
        std::string algorithm;
        std::string roomPath;
    };

    int roomDims[3] = {10, 6, 4};

    string roomPath = "Graphs_" + to_string(roomDims[0]) + "x" + to_string(roomDims[1])
                      + "x" + to_string(roomDims[2]);

    DataHandler dataHandler = DataHandler();

    dataHandler.runSimulation("RBAS",
                              0.9,
                              2,
                              0.7,
                              false,
                              16,
                              4,
                              100,
                              50,
                              100,
                              roomDims);


}
