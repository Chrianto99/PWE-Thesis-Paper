//
// Created by Christos on 6/14/2025.
//

#ifndef PWEOPTIMIZATION_SOLUTION_H
#define PWEOPTIMIZATION_SOLUTION_H

#endif //PWEOPTIMIZATION_SOLUTION_H

#include "Propagation/SystemState.h"
#include "map"
#include "vector"
#include <nlohmann/json.hpp>

#pragma once

using json = nlohmann::json;


class Solution {
private:
    vector<pair<int, int>> input; // (nodeId, modeId) pairs
    map<string, double> objectives; // map : objective name --> objective value
    double serviceRate; // defines the percentage of users that receive signal
    int frontRank; // front rank calculated by FNDS function in ParetoHandler
    double crowdingDistance; // crowding distance calculated by cd func in ParetoHandler

public:

    bool localSearchApplied;

    Solution() = default;

    explicit Solution(const SystemState &systemState) {
        this->input = systemState.getModeList();
        serviceRate = systemState.getServiceRate();
        objectives["averageDelaySpread"] = systemState.getAverageDelaySpread();
        objectives["averagePower"] = -systemState.getAveragePower();
        localSearchApplied = false;
        frontRank = 100;
        crowdingDistance = 100;
    }

    [[nodiscard]] int getFrontRank() const { return frontRank; }

    [[nodiscard]] double getCrowdingDistance() const { return crowdingDistance; }

    [[nodiscard]] const vector<pair<int, int>> &getModeList() const { return input; }

    [[nodiscard]] const map<string, double> &getObjectives() const { return objectives; }

    map<string, double> &getObjectives() { return objectives; }

    vector<pair<int, int>> &getModeList() { return input; }


    void setFrontRank(int rank) { frontRank = rank; }

    void setCrowdingDistance(double distance) { crowdingDistance = distance; }


    bool operator<(const Solution &other) const { return objectives < other.objectives; }

    bool operator==(const Solution &other) const { return objectives == other.objectives; }

    json toJson() const {
        json j;

        // Serialize input as array of arrays
        json inputJson = json::array();
        for (const auto &p: input) {
            inputJson.push_back({p.first, p.second});
        }

        // Serialize objectives (map)
        json objectivesJson;
        for (const auto &[name, value]: objectives) {
            objectivesJson[name] = value;
        }

        // Build final JSON
        j["input"] = inputJson;
        j["objectives"] = objectivesJson;


        return j;
    }
};



