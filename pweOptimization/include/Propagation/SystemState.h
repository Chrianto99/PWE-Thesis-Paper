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
    double averageDelaySpread, averagePower;
    double maxDelaySpread, minPower;
    double serviceRate;

public:

    SystemState() = default;
    SystemState(const SystemState&) = default;
    SystemState& operator=(const SystemState&) = default;

    SystemState(SystemState&&) = default;
    SystemState& operator=(SystemState&&) = default;

    void addDataToSystemState(double delaySpread, double power, double rayCount){
        receiverDelaySpreads.emplace_back(delaySpread);
        receiverPowers.emplace_back(power);
        receiverRayCounts.emplace_back(rayCount);
    }

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

    [[nodiscard]] double getAverageDelaySpread() const {
        return averageDelaySpread;
    }

    [[nodiscard]] double getAveragePower() const {
        return averagePower;
    }

    [[nodiscard]] const vector<pair<int,int>> &getModeList() const {
        return modeList;
    }

    [[nodiscard]] vector<pair<int,int>> &getModeList() {
        return modeList;
    }



    void setAverageDelaySpread() {
        double sum = std::accumulate(receiverDelaySpreads.begin(), receiverDelaySpreads.end(), 0.0);
        averageDelaySpread = sum / receiverDelaySpreads.size();

    }

    void setMaxDelaySpread(){
        maxDelaySpread = *std::max_element(receiverDelaySpreads.begin(), receiverDelaySpreads.end());
    }


    void setAveragePower() {
        double sum = std::accumulate(receiverPowers.begin(), receiverPowers.end(), 0.0);
        averagePower = sum / receiverPowers.size();
    }

    void setMinPower(){
        minPower = *std::min_element(receiverPowers.begin(), receiverPowers.end());
    }

    void setServiceRate(double serviceRate){
        this->serviceRate = serviceRate;
    }

    double getServiceRate(){
        return this->serviceRate;
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
