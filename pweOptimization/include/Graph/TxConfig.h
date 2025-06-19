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
    TxConfig(double g, double p, int lobes, double lambda)
            : gain(g), power(p), numLobes(lobes), wavelength(lambda) {}

    // Getters
    [[nodiscard]] double getGain() const noexcept { return gain; }
    [[nodiscard]] double getPower() const noexcept { return power; }
    [[nodiscard]] int getNumLobes() const noexcept { return numLobes; }
    [[nodiscard]] double getWavelength() const noexcept { return wavelength; }

    // Setters
    void setGain(double g) noexcept { gain = g; }
    void setPower(double p) noexcept { power = p; }
    void setNumLobes(int lobes) noexcept { numLobes = lobes; }
    void setWavelength(double lambda) noexcept { wavelength = lambda; }

    friend void to_json(nlohmann::json& j, const TxConfig& tC);
    friend void from_json(const nlohmann::json& j, TxConfig& tC);

};


#endif //PWEOPTIMIZATION_TXCONFIG_H
