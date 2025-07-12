//
// Created by Christos on 4/7/2025.
//

#include <cmath>
#include "Propagation/RayHandler.h"


SystemState RayHandler::propagate() {

    vector<Ray> currentRays = graph->getInputRays();

    while (!currentRays.empty()) {

        for (Ray &ray: currentRays) {

            reflectRay(ray);
        }

        currentRays.clear();
        currentRays = newRays;
        newRays.clear();
    }

    estimateSignal();
    restoreSystem();

    SystemState output = std::move(systemState);
    systemState = SystemState();
    return output;

}




void RayHandler::reflectRay(Ray &ray) {

    Node &currentNode = graph->getNode(ray.getCurrentNodeId());
    Edge &currentEdge = graph->getEdge(ray.getLastEdgeId());

    if (!currentNode.isActive()) {
        int modeChosen = modeHandler.chooseMode(currentNode.getId());
        currentNode.setActiveMode(modeChosen);
        currentNode.setActive(true);
        std::pair<int, int> nodeModePair{currentNode.getId(), modeChosen};
        systemState.addActiveMode(nodeModePair);
    }

    string key = to_string(currentEdge.getId()) + " " + to_string(currentNode.getActiveMode());

    const vector<double> &outputDist = currentNode.getDistFromRoutingTable(key);

    for (const double &value: outputDist) {
        int outputEdgeId = (int) floor(value);
        Edge &newEdge = graph->getEdge(outputEdgeId);
        Node &destNode = graph->getNode(newEdge.getDestNodeId());

        double gain = value - outputEdgeId;
        double pathLoss = newEdge.getPathLoss();
        double totalLength = ray.getLength() + newEdge.getLength();
        double totalPower = ray.getPower() * pathLoss * gain;

        if (totalPower < threshold) continue;

        ray.addEdge(outputEdgeId);
        Ray newRay = Ray(totalPower, totalLength, destNode.getId(), ray.getEdges());

        if (destNode.getType() == "Rx") destNode.addToRays(newRay);

        else newRays.push_back(newRay);




    }
}

void RayHandler::estimateSignal() {

    auto &receivers = graph->getReceivers();

    for (Node *nodePtr: receivers) {

        Node &receiver = *nodePtr;
        if (receiver.getRays().empty()){
           systemState.addDataToSystemState(0,0,0);
           continue;
        }
        if (receiver.getRays().size() == 1){
            double power = receiver.getRays().front().getPower();
            systemState.addDataToSystemState(0,power,1);
            continue;
        }
        int numRays = 0;
        double power = 0, delaySpread = 0;
        double mean_delay = 0, mean_delay_sq = 0;
        double a = 0, d = 0;
        double time = 0;
        for (const Ray &ray: receiver.getRays()) {
            power += ray.getPower();
            time = ray.getLength() / C;


            a += ray.getPower() * time;
            d += ray.getPower() * time * time;
            numRays++;
        }
        mean_delay = a / power;
        mean_delay_sq = d / power;
        delaySpread = sqrt(mean_delay_sq - (mean_delay * mean_delay));
        double tolerance = 1e-14;  // Adjust the tolerance as necessary

        if (abs(delaySpread) < tolerance) delaySpread = 0;

        systemState.addDataToSystemState(delaySpread, power, numRays);

    }
    systemState.setMaxDelaySpread();
    systemState.setMinPower();


}



void RayHandler::restoreSystem() {

    auto &receivers = graph->getReceivers();

    for (Node *receiver : receivers ){
        receiver->clearRays();
    }
    auto &allNodes = graph->getAllNodes();

    for (Node &node : allNodes){
        node.setActive(false);
    }

}

SystemState RayHandler::propagateRandom() {

    modeHandler.activateRandomModes(systemState);
    std::vector<Ray> currentRaysCopy = graph->getInputRays();
    std::vector<Ray> currentRays = currentRaysCopy;

    while (!currentRays.empty()) {

        for (Ray &ray: currentRays) {

            reflectRay(ray);
        }

        currentRays.clear();
        currentRays = newRays;
        newRays.clear();
    }

    estimateSignal();
    restoreSystem();

    SystemState output = std::move(systemState);
    systemState = SystemState();
    return output;

}

SystemState RayHandler::propagateGivenModes(const vector<pair<int,int>> &modeList) {

    for (pair pair : modeList){
        Node &node = graph->getNode(pair.first);
        node.setActiveMode(pair.second);
        node.setActive(true);
        systemState.addActiveMode(pair);
    }

    std::vector<Ray> currentRaysCopy = graph->getInputRays();
    std::vector<Ray> currentRays = currentRaysCopy;

    while (!currentRays.empty()) {

        for (Ray &ray: currentRays) {

            reflectRay(ray);
        }

        currentRays.clear();
        currentRays = newRays;
        newRays.clear();
    }

    estimateSignal();
    restoreSystem();

    SystemState output = std::move(systemState);
    systemState = SystemState();
    return output;

}






