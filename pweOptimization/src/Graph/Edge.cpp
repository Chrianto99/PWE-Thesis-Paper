//
// Created by Christos on 3/18/2025.
//

#include "Graph/Edge.h"


void to_json(nlohmann::json& j, const Edge& e) {
    j = {
            {"id", e.id},
            {"startNode_id", e.startNode_id},
            {"destNode_id", e.destNode_id},
            {"length", e.length},
            {"pathLoss", e.pathLoss},
    };
}

void from_json(const nlohmann::json& j, Edge& e) {
    j.at("id").get_to(e.id);
    j.at("startNode_id").get_to(e.startNode_id);
    j.at("destNode_id").get_to(e.destNode_id);
    j.at("length").get_to(e.length);
    j.at("pathLoss").get_to(e.pathLoss);

}