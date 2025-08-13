//
// Created by Christos on 4/7/2025.
//

#ifndef PWEOPTIMIZATION_TXCONFIG_H
#define PWEOPTIMIZATION_TXCONFIG_H

#include <nlohmann/json.hpp>


class TxConfig {

private:
    double gain;
    double power;
    int numLobes;
    double wavelength;

public:
    // Constructor (optional)
    TxConfig() = default;

    friend void to_json(nlohmann::json &j, const TxConfig &t) {
        j = {
                {"gain",       t.gain},
                {"power",      t.power},
                {"numLobes",   t.numLobes},
                {"wavelength", t.wavelength}
        };
    }

    friend void from_json(const nlohmann::json &j, TxConfig &t) {
        j.at("gain").get_to(t.gain);
        j.at("power").get_to(t.power);
        j.at("numLobes").get_to(t.numLobes);
        j.at("wavelength").get_to(t.wavelength);
    }

};


#endif //PWEOPTIMIZATION_TXCONFIG_H
