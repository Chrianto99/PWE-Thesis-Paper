//
// Created by Christos on 3/18/2025.
//

#include "Graph/Node.h"

void to_json(nlohmann::json& j, const Node& n) {
    j = {
            {"id", n.id},
            {"numberOfModes", n.numberOfModes},
            {"routingTable", n.routingTable},
            {"type", n.type},
    };
}

void from_json(const nlohmann::json& j, Node& n) {
    j.at("id").get_to(n.id);
    j.at("numberOfModes").get_to(n.numberOfModes);
    j.at("routingTable").get_to(n.routingTable);
    j.at("type").get_to(n.type);

}
