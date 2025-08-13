//
// Created by Christos on 3/18/2025.
//
#include <string>  // Include string library
#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>

#include "Propagation/Ray.h"
#include <nlohmann/json.hpp>


#ifndef PWEOPTIMIZATION_NODE_H
#define PWEOPTIMIZATION_NODE_H

using namespace std;

class Node {

private:
    int id;
    int activeMode;
    bool active, blocked;
    int numberOfModes;
    unordered_map<string, vector<double>> routingTable;
    string type;
    vector<Ray> rays;


public:

    Node() = default;

    Node(int id, int mode, bool isActive, const std::string &nodeType, const std::vector<Ray> &rayVec)
            : id(id), activeMode(mode), active(isActive), type(nodeType), rays(rayVec) {}

    // Getters
    [[nodiscard]] int getId() const noexcept { return id; }

    [[nodiscard]] int getActiveMode() const noexcept { return activeMode; }

    [[nodiscard]] int getNumModes() const noexcept { return numberOfModes; }

    [[nodiscard]] bool isActive() const noexcept { return active; }

    [[nodiscard]] const std::string &getType() const noexcept { return type; }

    [[nodiscard]] const std::vector<Ray> &getRays() const noexcept { return rays; }


    // Setters
    void setActiveMode(int mode) noexcept { activeMode = mode; }

    void setActive(bool isActive) noexcept { active = isActive; }

    void addToRays(Ray &ray) noexcept { rays.emplace_back(ray); }

    void clearRays() { rays.clear(); }

    const vector<double> &getDistFromRoutingTable(string &key) {
        return routingTable.at(key);
    }

    //json
    friend void to_json(nlohmann::json& j, const Node& n) {
        j = {
                {"id", n.id},
                {"numberOfModes", n.numberOfModes},
                {"routingTable", n.routingTable},
                {"type", n.type},
        };
    }

    friend void from_json(const nlohmann::json& j, Node& n) {
        j.at("id").get_to(n.id);
        j.at("numberOfModes").get_to(n.numberOfModes);
        j.at("routingTable").get_to(n.routingTable);
        j.at("type").get_to(n.type);

    }


};


#endif //PWEOPTIMIZATION_NODE_H
