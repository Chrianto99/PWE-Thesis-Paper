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

    int roomDims[3] = {10, 6, 4};

    DataHandler dataHandler = DataHandler();

    dataHandler.setMOACOParams(2, 0.9, 0.7);
    dataHandler.setNSGAParams(0.03);

    dataHandler.runSimulation("RBAS",
                              false,
                              16,
                              4,
                              100,
                              50,
                              100,
                              roomDims);


}
