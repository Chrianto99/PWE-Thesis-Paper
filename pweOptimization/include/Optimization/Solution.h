//
// Created by Christos on 6/14/2025.
//

#ifndef PWEOPTIMIZATION_SOLUTION_H
#define PWEOPTIMIZATION_SOLUTION_H

#endif //PWEOPTIMIZATION_SOLUTION_H
#include "Propagation/SystemState.h"
#pragma once
class Solution{
private:

    SystemState systemState;
    int frontRank, crowdingDistanceRank;
    double crowdingDistance;

public:

    Solution() = default;

    Solution(SystemState &systemState){
        this->systemState = systemState;
    }
    int getFrontRank() const {
        return frontRank;
    }

    void setFrontRank(int rank) {
        frontRank = rank;
    }

    double getCrowdingDistance() const {
        return crowdingDistance;
    }

    void setCrowdingDistance(double distance) {
        crowdingDistance = distance;
    }

    int getCrowdingDistanceRank() const {
        return crowdingDistance;
    }

    void setCrowdingDistanceRank(int distance) {
        crowdingDistance = distance;
    }

    double getMinPower() const{
        return systemState.getMinPower();
    }

    double getMaxDelaySpread() const{
        return systemState.getMaxDelaySpread();
    }

    [[nodiscard]]  const vector<pair<int,int>> &getModeList() const {
        return systemState.getModeList();
    }

    [[nodiscard]]  vector<pair<int,int>> &getModeList() {
        return systemState.getModeList();
    }

    void addActiveMode(pair<int,int> pair) {
        systemState.addActiveMode(pair);
    }

    bool operator<(const Solution& other) const {
        // First order by frontRank (ascending)
        if (frontRank != other.frontRank)
            return frontRank < other.frontRank;

        // Then order by crowdingDistance (descending)
        if (crowdingDistance != other.crowdingDistance)
            return crowdingDistance > other.crowdingDistance; // note '>' because higher distance is better

        // Then order by crowdingDistanceRank (ascending)
        if (crowdingDistanceRank != other.crowdingDistanceRank)
            return crowdingDistanceRank < other.crowdingDistanceRank;

        // As last resort, you could compare systemState if you have a way to compare it
        // For now, fallback to false (equal)
        return false;
    }

    SystemState& getSystemState() {
        return systemState;
    }

};