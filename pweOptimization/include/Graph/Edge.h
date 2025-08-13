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

    [[nodiscard]] int getDestNodeId() const noexcept { return destNode_id; }

    [[nodiscard]] double getLength() const noexcept { return length; }

    [[nodiscard]] double getPathLoss() const noexcept { return pathLoss; }


    friend void to_json(nlohmann::json &j, const Edge &e) {
        j = {
                {"id",           e.id},
                {"startNode_id", e.startNode_id},
                {"destNode_id",  e.destNode_id},
                {"length",       e.length},
                {"pathLoss",     e.pathLoss},
        };
    }

    friend void from_json(const nlohmann::json &j, Edge &e) {
        j.at("id").get_to(e.id);
        j.at("startNode_id").get_to(e.startNode_id);
        j.at("destNode_id").get_to(e.destNode_id);
        j.at("length").get_to(e.length);
        j.at("pathLoss").get_to(e.pathLoss);

    }

};


#endif //PWEOPTIMIZATION_EDGE_H
