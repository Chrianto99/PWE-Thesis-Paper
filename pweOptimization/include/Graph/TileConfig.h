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
    TileConfig(int elements, double spacing, double gain, double maxG, double dim, double lambda)
            : numElements(elements), elementSpacing(spacing), elementGain(gain),
              maxGain(maxG), maxDim(dim), wavelength(lambda) {}

    // Getters
    [[nodiscard]] int getNumElements() const noexcept { return numElements; }
    [[nodiscard]] double getElementSpacing() const noexcept { return elementSpacing; }
    [[nodiscard]] double getElementGain() const noexcept { return elementGain; }
    [[nodiscard]] double getMaxGain() const noexcept { return maxGain; }
    [[nodiscard]] double getMaxDim() const noexcept { return maxDim; }
    [[nodiscard]] double getWavelength() const noexcept { return wavelength; }

    // Setters
    void setNumElements(int elements) noexcept { numElements = elements; }
    void setElementSpacing(double spacing) noexcept { elementSpacing = spacing; }
    void setElementGain(double gain) noexcept { elementGain = gain; }
    void setMaxGain(double maxG) noexcept { maxGain = maxG; }
    void setMaxDim(double dim) noexcept { maxDim = dim; }
    void setWavelength(double lambda) noexcept { wavelength = lambda; }

    friend void to_json(nlohmann::json& j, const TileConfig& tC);
    friend void from_json(const nlohmann::json& j, TileConfig& tC);




};


#endif //PWEOPTIMIZATION_TILECONFIG_H
