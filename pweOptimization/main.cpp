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
    g->loadGraph("Graphs_15x10x5/Rx_4/Tiles_16/Graph_2.json", *g);


//    auto start = std::chrono::high_resolution_clock::now();
//
//    NSGAII nsga = NSGAII(*g,50,100,0.5,0);
//    nsga.run();
//
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = duration_cast<std::chrono::milliseconds >(end - start);
//    auto durationPerPropagation = duration.count() ;
//
//    cout << "Time taken: " << durationPerPropagation << " ms" << endl;
//
//    start = std::chrono::high_resolution_clock::now();
//
//    RBAS rbas = RBAS(*g,50,100,0.8,5);
//    rbas.run();
//
//    end = std::chrono::high_resolution_clock::now();
//    duration = duration_cast<std::chrono::milliseconds>(end - start);
//    durationPerPropagation = duration.count() ;



//    cout << "Time taken: " << durationPerPropagation << " μs" << endl;

    for (int i = 0; i < 10; ++i) {
        cout << i << endl;
        map<int,vector<Solution>> currentOutput;
        RBAS alg = RBAS(*g,50,100,0.8,2);
        alg.run();
        map<int,vector<Solution>> output = ParetoHandler::mergeOutputs(currentOutput, alg.getOutput());
        currentOutput = alg.getOutput();
        if (i == 9){
            cout << "a" << endl;
        }
    }



}
