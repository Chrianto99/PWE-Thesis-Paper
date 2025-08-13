//
// Created by Christos on 7/12/2025.
//

#ifndef PWEOPTIMIZATION_POINT_H
#define PWEOPTIMIZATION_POINT_H

#endif //PWEOPTIMIZATION_POINT_H

#include "vector"
#include "string"

using namespace std;

class Point {
private:
    vector<double> cords;

public:

    Point(const map<string, double> &objectives, const vector<string> &objectiveLabels) {

        for (auto &label: objectiveLabels) {
            cords.push_back(objectives.at(label));
        }

    }

};
