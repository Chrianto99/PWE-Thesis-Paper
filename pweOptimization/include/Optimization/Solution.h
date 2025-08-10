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


class Solution{
private:

    vector<pair<int, int>> input;
    vector<string> print;
    map<string,double> objectives;
    int frontRank, crowdingDistanceRank;
    double crowdingDistance;
    double servicePercent; //Defines the percentage of users that are satisfied

public:

    Solution() = default;

    Solution(const SystemState &systemState){
        this->input = systemState.getModeList();
        objectives["averageDelaySpread"] = systemState.getAverageDelaySpread();
        objectives["averagePower"] = -systemState.getAveragePower();
        for (auto &pair : input) {
            print.push_back(to_string(pair.first) + "." + to_string(pair.second));
        }


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

    vector<pair<int,int>> &getModeList(){
        return input;
    }

    const vector<pair<int,int>> &getModeList() const{
        return input;
    }

    const map<string,double> &getObjectives() const{
        return objectives;
    }

    map<string,double> &getObjectives() {
        return objectives;
    }



//    bool operator<(const Solution& other) const {
//        // First order by frontRank (ascending)
//        if (frontRank != other.frontRank)
//            return frontRank < other.frontRank;
//
//        // Then order by crowdingDistance (descending)
//        if (crowdingDistance != other.crowdingDistance)
//            return crowdingDistance > other.crowdingDistance; // note '>' because higher distance is better
//
//        // Then order by crowdingDistanceRank (ascending)
//        if (crowdingDistanceRank != other.crowdingDistanceRank)
//            return crowdingDistanceRank < other.crowdingDistanceRank;
//
//        // As last resort, you could compare systemState if you have a way to compare it
//        // For now, fallback to false (equal)
//        return false;
//    }

    bool operator<(const Solution& other) const {
        return objectives < other.objectives; // lexicographical comparison of std::map
    }

    json toJson() const {
        json j;

        // Serialize input as array of arrays
        json inputJson = json::array();
        for (const auto &p : input) {
            inputJson.push_back({p.first, p.second});
        }

        // Serialize print as array of strings
        json printJson = print;

        // Serialize objectives (map)
        json objectivesJson;
        for (const auto &[name, value] : objectives) {
            objectivesJson[name] = value;
        }

        // Build final JSON
        j["input"] = inputJson;
        j["objectives"] = objectivesJson;


        return j;
    }
};



