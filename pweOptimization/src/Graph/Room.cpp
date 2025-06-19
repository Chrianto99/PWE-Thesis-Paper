//
// Created by Christos on 4/7/2025.
//

#include "Graph/Room.h"

void to_json(nlohmann::json& j, const Room& r) {
    j = {
            {"numTiles", r.numTiles},
            {"numReceivers", r.numReceivers},
            {"alpha", r.alpha}
    };
}

void from_json(const nlohmann::json& j, Room& r) {
    j.at("numTiles").get_to(r.numTiles);
    j.at("numReceivers").get_to(r.numReceivers);
    j.at("alpha").get_to(r.alpha);
}