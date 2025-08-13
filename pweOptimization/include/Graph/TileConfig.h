//
// Created by Christos on 4/7/2025.
//

#ifndef PWEOPTIMIZATION_TILECONFIG_H
#define PWEOPTIMIZATION_TILECONFIG_H

#include <nlohmann/json.hpp>


class TileConfig {

    int numElements;
    double elementSpacing;
    double elementGain;
    double maxGain;
    double maxDim;
    double wavelength;

public:
    // Constructor (optional)
    TileConfig() = default;

    friend void to_json(nlohmann::json &j, const TileConfig &t) {
        j = {
                {"numElements",    t.numElements},
                {"elementSpacing", t.elementSpacing},
                {"elementGain",    t.elementGain},
                {"maxGain",        t.maxGain},
                {"maxDim",         t.maxDim},
                {"wavelength",     t.wavelength}
        };
    }

    friend void from_json(const nlohmann::json &j, TileConfig &t) {
        j.at("numElements").get_to(t.numElements);
        j.at("elementSpacing").get_to(t.elementSpacing);
        j.at("elementGain").get_to(t.elementGain);
        j.at("maxGain").get_to(t.maxGain);
        j.at("maxDim").get_to(t.maxDim);
        j.at("wavelength").get_to(t.wavelength);
    }


};


#endif //PWEOPTIMIZATION_TILECONFIG_H
