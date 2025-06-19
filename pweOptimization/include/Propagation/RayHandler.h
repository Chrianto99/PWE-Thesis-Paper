//
// Created by Christos on 4/7/2025.
//

#ifndef PWEOPTIMIZATION_RAYHANDLER_H
#define PWEOPTIMIZATION_RAYHANDLER_H


#include "Graph/Graph.h"
#include "Propagation/Ray.h"
#include "SystemState.h"
#include "ModeHandler.h"

class RayHandler {


private:
    Graph* graph;
    std::vector<Ray> newRays;
    SystemState systemState;
    ModeHandler modeHandler;
public:
    const ModeHandler &getModeHandler() const;

private:
    double threshold;
    const double C = 299792458;

public:

    RayHandler(Graph& graph){

        this->graph = &graph;
        modeHandler = ModeHandler(graph, 1);
        threshold = pow(10,-12);

    }

    SystemState propagate();

    SystemState propagateRandom();

    SystemState propagateGivenModes(const vector<pair<int,int>> &modeList);

    void reflectRay(Ray& ray);

    void estimateSignal();

    void restoreSystem();

    SystemState &getSystemState(){
        return systemState;
    }

    ModeHandler &getModeHandler()  {
        return modeHandler;
    }


};


#endif //PWEOPTIMIZATION_RAYHANDLER_H
