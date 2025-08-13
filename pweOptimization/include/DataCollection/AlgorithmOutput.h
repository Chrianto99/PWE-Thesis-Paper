//
// Created by Christos on 7/12/2025.
//

#ifndef PWEOPTIMIZATION_ALGORITHMOUTPUT_H
#define PWEOPTIMIZATION_ALGORITHMOUTPUT_H

#include "map"
#include "Optimization/Solution.h"
#include "Point.h"
#include <nlohmann/json.hpp>
#include <fstream>


using namespace std;
using json = nlohmann::json;

class AlgorithmOutput {
private:
    map<int, vector<Solution>> output;
    map<int, vector<vector<double>>> fronts;
    map<int, double> hyperVolumes;
    vector<string> objectiveLabels;

public:
    AlgorithmOutput() = default;

    AlgorithmOutput(const map<int, vector<Solution>> &input, const vector<string> &objectiveLabels) {
        output = input;
        this->objectiveLabels = objectiveLabels;
    }

    void setFronts(const map<int, vector<vector<double>>> &fronts) {
        this->fronts = fronts;
    }

    void setHyperVolumes(const map<int, double> &hyperVolumes) {
        this->hyperVolumes = hyperVolumes;
    }


    [[nodiscard]] const map<int, vector<vector<double>>> &getFronts() const {
        return fronts;
    }

    void writeToJson(const std::string &folderName, int graphID, int numTiles, int numUsers) const {
        namespace fs = std::filesystem;

        // Create the main directory
        fs::create_directories(folderName);

        // Create the subdirectory path
        std::string subDirName = std::to_string(numTiles) + "Tiles_" + std::to_string(numUsers) + "Users";
        fs::path subDirPath = fs::path(folderName) / subDirName;
        fs::create_directories(subDirPath);

        // Build the filename
        std::string fileName = "Graph_" + std::to_string(graphID) + ".json";

        // Full file path
        fs::path filePath = subDirPath / fileName;

        json j;
        j["objectiveLabels"] = objectiveLabels;

        // Save the output map
//        for (const auto& [key, solutions] : output) {
//            for (const auto& s : solutions) {
//                json sJson;
//                // Assume Solution class has a method toJson() (you'll implement it below)
//                sJson = s.toJson();
//                j["output"][std::to_string(key)].push_back(sJson);
//            }
//        }

        // Save the fronts and hypervolumes
        j["fronts"] = fronts;
        j["hyperVolumes"] = hyperVolumes;

        // Write to file
        std::ofstream outFile(filePath);
        if (!outFile) {
            throw std::runtime_error("Failed to write to ");
        }
        outFile << j.dump(4); // Pretty-print with 4-space indent
    }
};

#endif //PWEOPTIMIZATION_ALGORITHMOUTPUT_H



