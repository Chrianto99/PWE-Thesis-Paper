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

    // Setters
    void setPower(double p) noexcept { power = p; }

    void setLength(double len) noexcept { length = len; }

    void setCurrentNodeId(int nodeId) noexcept { currentNode_id = nodeId; }

    void setEdges(const std::vector<int> &edgeList) noexcept { edges = edgeList; }

    void setEdges(std::vector<int> &&edgeList) noexcept { edges = std::move(edgeList); }

    // Optional: Add method to append to edges
    void addEdge(int edgeId) noexcept { edges.push_back(edgeId); }

    friend void to_json(nlohmann::json& j, const Ray& r);
    friend void from_json(const nlohmann::json& j, Ray& r);


};


#endif //PWEOPTIMIZATION_RAY_H
