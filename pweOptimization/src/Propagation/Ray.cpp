//
// Created by Christos on 3/18/2025.
//

#include "Propagation/Ray.h"

void to_json(nlohmann::json& j, const Ray& r) {
    j = {
            {"power", r.power},
            {"length", r.length},
            {"currentNode_id", r.currentNode_id},
            {"edges", r.edges}
    };
}

void from_json(const nlohmann::json& j, Ray& r) {
    j.at("power").get_to(r.power);
    j.at("length").get_to(r.length);
    j.at("currentNode_id").get_to(r.currentNode_id);
    j.at("edges").get_to(r.edges);
}