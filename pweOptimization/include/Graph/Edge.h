//
// Created by Christos on 3/18/2025.
//

#ifndef PWEOPTIMIZATION_EDGE_H
#define PWEOPTIMIZATION_EDGE_H

#include <nlohmann/json.hpp>



class Edge {

private:
    int id;
    int startNode_id;
    int destNode_id;
    double length;
    double pathLoss;

public:
    Edge() = default;
    Edge(int id, int start, int dest, double len, double loss, int key)
            : id(id), startNode_id(start), destNode_id(dest),
              length(len), pathLoss(loss) {}

    // Getters
    [[nodiscard]] int getId() const noexcept { return id; }
    [[nodiscard]] int getStartNodeId() const noexcept { return startNode_id; }
    [[nodiscard]] int getDestNodeId() const noexcept { return destNode_id; }
    [[nodiscard]] double getLength() const noexcept { return length; }
    [[nodiscard]] double getPathLoss() const noexcept { return pathLoss; }

    // Setters
    void setId(int newId) noexcept { id = newId; }
    void setStartNodeId(int start) noexcept { startNode_id = start; }
    void setDestNodeId(int dest) noexcept { destNode_id = dest; }
    void setLength(double len) noexcept { length = len; }
    void setPathLoss(double loss) noexcept { pathLoss = loss; }

    friend void to_json(nlohmann::json& j, const Edge& e);
    friend void from_json(const nlohmann::json& j, Edge& e);

};


#endif //PWEOPTIMIZATION_EDGE_H
