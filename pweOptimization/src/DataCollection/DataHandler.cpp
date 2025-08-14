//
// Created by Christos on 7/12/2025.
//
#include "DataCollection/DataHandler.h"


AlgorithmOutput
DataHandler::returnData(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels) {

    data = AlgorithmOutput(output, objectiveLabels);

    createFronts(output, objectiveLabels);

    calculateHyperVolumes(data.getFronts());

    return data;

}

map<int, vector<vector<double>>>
DataHandler::createFronts(const map<int, vector<Solution>> &output, const vector<string> &objectiveLabels) {
    map<int, vector<vector<double>>> extractedFronts;

    for (const auto &[repMark, solutions]: output) {

        vector<vector<double>> front;
        for (const auto &sol: solutions) {

            vector<double> point;
            for (auto &label: objectiveLabels) {
                point.push_back(sol.getObjectives().at(label));
            }
            front.push_back(point);

        }
        extractedFronts[repMark] = front;

    }

    data.setFronts(extractedFronts);

    return extractedFronts;
}

void DataHandler::calculateHyperVolumes(const map<int, vector<vector<double>>> &fronts) {
    map<int, double> hyperVolumes;
    vector<double> referencePoint = computeReferencePoint(fronts, 10e-12);

    for (const auto &[frontRank, points]: fronts) {
        double hv = 0.0;

        // Sort the front by the first objective (ascending)
        vector<vector<double>> sortedPoints = points;
        sort(sortedPoints.begin(), sortedPoints.end(), [](const vector<double> &a, const vector<double> &b) {
            return a[0] < b[0];
        });

        double prevObj1 = referencePoint[0];
        for (const auto &p: sortedPoints) {
            double width = prevObj1 - p[0];
            double height = referencePoint[1] - p[1];
            if (width > 0 && height > 0)
                hv += width * height;
            prevObj1 = p[0];
        }

        hyperVolumes[frontRank] = hv;
    }

    data.setHyperVolumes(hyperVolumes);
}

vector<double> DataHandler::computeReferencePoint(const map<int, vector<vector<double>>> &fronts, double epsilon) {
    if (fronts.empty()) {
        throw std::invalid_argument("Fronts map is empty");
    }

    // Determine the number of objectives (dimensions)
    int numObjectives = fronts.begin()->second.front().size();
    vector<double> reference(numObjectives, -std::numeric_limits<double>::infinity());

    for (const auto &[repMark, front]: fronts) {
        for (const auto &point: front) {
            for (int i = 0; i < numObjectives; ++i) {
                reference[i] = max(reference[i], point[i]);
            }
        }
    }

    // Add epsilon to each dimension
    for (double &val: reference) {
        val += epsilon;
    }

    return reference;
}


