//
// Created by Christos on 3/18/2025.
//
#include "iostream"
#include "vector"
#include "Graph/Edge.h"
#include "nlohmann/json.hpp"


#ifndef PWEOPTIMIZATION_RAY_H
#define PWEOPTIMIZATION_RAY_H


class Ray {

private:
    double power;
    double length;
    int currentNode_id;
    std::vector<int> edges;


public:
    // Constructor (optional)
    Ray() = default;

    Ray(double p, double len, int nodeId, const std::vector<int> &edgeList)
            : power(p), length(len), currentNode_id(nodeId), edges(edgeList) {}

    // Getters
    [[nodiscard]] double getPower() const noexcept { return power; }

    [[nodiscard]] double getLength() const noexcept { return length; }

    [[nodiscard]] int getCurrentNodeId() const noexcept { return currentNode_id; }

    [[nodiscard]] const std::vector<int> &getEdges() const noexcept { return edges; }

    [[nodiscard]] int getLastEdgeId() const noexcept { return edges.back(); }

    // Optional: Add method to append to edges
    void addEdge(int edgeId) noexcept { edges.push_back(edgeId); }

    friend void to_json(nlohmann::json &j, const Ray &r) {
        j = {
                {"power",          r.power},
                {"length",         r.length},
                {"currentNode_id", r.currentNode_id},
                {"edges",          r.edges}
        };
    }

    friend void from_json(const nlohmann::json &j, Ray &r) {
        j.at("power").get_to(r.power);
        j.at("length").get_to(r.length);
        j.at("currentNode_id").get_to(r.currentNode_id);
        j.at("edges").get_to(r.edges);
    }

};


#endif //PWEOPTIMIZATION_RAY_H
