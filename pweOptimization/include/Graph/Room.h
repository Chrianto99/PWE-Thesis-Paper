//
// Created by Christos on 4/7/2025.
//

#ifndef PWEOPTIMIZATION_ROOM_H
#define PWEOPTIMIZATION_ROOM_H
#include <nlohmann/json.hpp>



class Room {
private:

    int numTiles;
    int numReceivers;
    int alpha;


public:

    Room() = default;


    // Getters
    [[nodiscard]] int getNumTiles() const noexcept { return numTiles; }
    [[nodiscard]] int getNumReceivers() const noexcept { return numReceivers; }
    [[nodiscard]] int getAlpha() const noexcept { return alpha; }

    // Setters
    void setNumTiles(int tiles) noexcept { numTiles = tiles; }
    void setNumReceivers(int receivers) noexcept { numReceivers = receivers; }
    void setAlpha(int a) noexcept { alpha = a; }

    friend void to_json(nlohmann::json& j, const Room& r);
    friend void from_json(const nlohmann::json& j, Room& r);

};


#endif //PWEOPTIMIZATION_ROOM_H
