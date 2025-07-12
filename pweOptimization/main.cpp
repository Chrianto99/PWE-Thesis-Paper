#include <iostream>
#include <fstream>
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Optimization/NSGA-II.h"
#include "Optimization/RBAS.h"
#include <chrono>



#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {

    Graph* g = new Graph();
    g->loadGraph("Graphs_15x10x5/Rx_4/Tiles_16/Graph_0.json", *g);


    auto start = std::chrono::high_resolution_clock::now();

    map<int,set<Solution>> currentOutput;
    for (int i = 0; i < 100; ++i) {
        cout << i << endl;
        //RBAS alg = RBAS(*g,24,200,0.8,2);
        NSGAII alg = NSGAII(*g,24,200,0.5,0.02);
        alg.run();
        map<int,set<Solution>> output = ParetoHandler::mergeOutputs(currentOutput, alg.getOutput());
        currentOutput = output;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds >(end - start);
    auto durationPerPropagation = duration.count() / 100;
    cout << "Time taken: " << durationPerPropagation << " ms" << endl;



}
