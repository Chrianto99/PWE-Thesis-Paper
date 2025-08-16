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
    ModeHandler &getModeHandler()  { return modeHandler; }

    // Emulates system propagation , picking modes according to distribution
    // Distribution defaults to uniform
    // Uses reflectRay , estimateSignal() and restoreSystem()
    SystemState propagate();

    // Does the same but given a predefined set of active EM functions
    SystemState propagateGivenModes(const vector<pair<int,int>> &modeList);

    void reflectRay(Ray& ray);

    void estimateSignal();

    void restoreSystem();

};


#endif //PWEOPTIMIZATION_RAYHANDLER_H
