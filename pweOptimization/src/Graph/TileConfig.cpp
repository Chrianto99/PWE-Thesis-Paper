//
// Created by Christos on 4/7/2025.
//

#include "Graph/TileConfig.h"

void to_json(nlohmann::json& j, const TileConfig& t) {
    j = {
            {"numElements", t.numElements},
            {"elementSpacing", t.elementSpacing},
            {"elementGain", t.elementGain},
            {"maxGain", t.maxGain},
            {"maxDim", t.maxDim},
            {"wavelength", t.wavelength}
    };
}

void from_json(const nlohmann::json& j, TileConfig& t) {
    j.at("numElements").get_to(t.numElements);
    j.at("elementSpacing").get_to(t.elementSpacing);
    j.at("elementGain").get_to(t.elementGain);
    j.at("maxGain").get_to(t.maxGain);
    j.at("maxDim").get_to(t.maxDim);
    j.at("wavelength").get_to(t.wavelength);
}
