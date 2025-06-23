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
    NSGAII nsga = NSGAII(*g,50,100,0.5,0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - start);
    auto durationPerPropagation = duration.count() ;

    nsga.run();

    cout << "Time taken: " << durationPerPropagation << " μs" << endl;

    start = std::chrono::high_resolution_clock::now();
    RBAS rbas = RBAS(*g,50,100,0.8,5);
    end = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(end - start);
    durationPerPropagation = duration.count() ;

    rbas.run();

    cout << "Time taken: " << durationPerPropagation << " μs" << endl;



}
