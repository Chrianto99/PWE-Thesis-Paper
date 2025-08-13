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

    friend void to_json(nlohmann::json &j, const Room &r) {
        j = {
                {"numTiles",     r.numTiles},
                {"numReceivers", r.numReceivers},
                {"alpha",        r.alpha}
        };
    }

    friend void from_json(const nlohmann::json &j, Room &r) {
        j.at("numTiles").get_to(r.numTiles);
        j.at("numReceivers").get_to(r.numReceivers);
        j.at("alpha").get_to(r.alpha);
    }
};


#endif //PWEOPTIMIZATION_ROOM_H
