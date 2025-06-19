#include <iostream>
#include <fstream>
#include "Graph/Graph.h"
#include "Propagation/RayHandler.h"
#include "Optimization/NSGA-II.h"
#include <chrono>



#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {

    Graph* g = new Graph();
    g->loadGraph("data/Graphs_15x10x5/Rx_4/Tiles_16/Graph_0.json", *g);


//    auto start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 1000 ; ++i) {
//        rayHandler->propagate();
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Duration in milliseconds
//    auto duration = duration_cast<std::chrono::microseconds>(end - start);
//    auto durationPerPropagation = duration.count() / 1000;
//
//    cout << "Time taken: " << durationPerPropagation << " μs" << endl;
//
//    return 0;

    auto start = std::chrono::high_resolution_clock::now();
    NSGAII nsga = NSGAII(*g,50,100,0.5,0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - start);
    auto durationPerPropagation = duration.count() ;

    cout << "Time taken: " << durationPerPropagation << " μs" << endl;

    nsga.run();

}
