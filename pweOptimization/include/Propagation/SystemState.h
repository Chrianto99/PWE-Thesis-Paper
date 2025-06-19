//
// Created by Christos on 4/8/2025.
//

#include <vector>
#include "iostream"
#include <iomanip>  // for formatting
#include <algorithm>
#include <numeric>


#ifndef PWEOPTIMIZATION_SYSTEMSTATE_H
#define PWEOPTIMIZATION_SYSTEMSTATE_H

using namespace std;


class SystemState {
private:
    vector<pair<int,int>> modeList;
    vector<double> receiverDelaySpreads;
    vector<double> receiverPowers;
    vector<double> receiverRayCounts;
    double maxDelaySpread, minPower;

public:
    SystemState() = default;

    void addActiveMode(pair<int,int> pair) {
        modeList.emplace_back(pair);
    }

    void addToDelaySpreads(double delaySpread) {
        receiverDelaySpreads.push_back(delaySpread);
    }

    void addToPowers(double power) {
        receiverPowers.push_back(power);
    }

    void addToRayCounts(int rayCount) {
        receiverRayCounts.push_back(rayCount);
    }

    [[nodiscard]] double getMaxDelaySpread() const {
        return maxDelaySpread;
    }

    [[nodiscard]] double getMinPower() const {
        return minPower;
    }

    [[nodiscard]] const vector<pair<int,int>> &getModeList() const {
        return modeList;
    }

    [[nodiscard]] vector<pair<int,int>> &getModeList() {
        return modeList;
    }



    void setMaxDelaySpread() {
        maxDelaySpread = *std::max_element(receiverDelaySpreads.begin(), receiverDelaySpreads.end());
        //double sum = std::accumulate(receiverDelaySpreads.begin(), receiverDelaySpreads.end(), 0.0);
        //maxDelaySpread = sum / receiverDelaySpreads.size();

    }


    void setMinPower() {
        minPower = *std::min_element(receiverPowers.begin(), receiverPowers.end());
        double sum = std::accumulate(receiverPowers.begin(), receiverPowers.end(), 0.0);
        minPower = sum / receiverPowers.size();
    }

    void print() const {

        cout << "SystemState Contents:\n";

        cout << "Active Modes (nodeId.modeId):\n";

        for (pair<int,int> pair : modeList){
            cout << pair.first << "-" << pair.second << "  ";
        }
        cout << endl;

        cout << "Receiver Delay Spreads:\n";
        for (size_t i = 0; i < receiverDelaySpreads.size(); ++i)
            cout << "  [" << i << "] " << receiverDelaySpreads[i] << "\n";

        cout << "Receiver Powers:\n";
        for (size_t i = 0; i < receiverPowers.size(); ++i)
            cout << "  [" << i << "] " << receiverPowers[i] << "\n";

        cout << "Receiver Ray Counts:\n";
        for (size_t i = 0; i < receiverRayCounts.size(); ++i)
            cout << "  [" << i << "] " << receiverRayCounts[i] << "\n";

        cout << "Max Delay Spread: " << maxDelaySpread << "\n";
        cout << "Min Power: " << minPower << "\n";
    }

    void clear(){
        modeList.clear();
        receiverPowers.clear();
        receiverDelaySpreads.clear();
        receiverRayCounts.clear();

    }


};


#endif //PWEOPTIMIZATION_SYSTEMSTATE_H
