//
// Created by Christos on 3/18/2025.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Node.h"
#include "Edge.h"
#include "TxConfig.h"
#include "TileConfig.h"
#include "Room.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "Propagation/Ray.h"


using namespace std;
using json = nlohmann::json;

#ifndef PWEOPTIMIZATION_GRAPH_H
#define PWEOPTIMIZATION_GRAPH_H


class Graph {
private:
    vector<Node> allNodes;
    vector<Edge> allEdges;
    vector<Ray> inputRays;
    unordered_map<string, unordered_map<string, vector<double>>> routingTables;

    TxConfig txConfig;
    TileConfig tileConfig;
    Room room;

    vector<Node *> receivers;
    vector<Node *> tiles;

public:

    Node &getNode(int id) noexcept { return allNodes[id]; }

    [[nodiscard]] vector<Node> &getAllNodes() noexcept { return allNodes; }

    [[nodiscard]] Edge &getEdge(int id) noexcept { return allEdges[id]; }

    [[nodiscard]] const vector<Ray> &getInputRays() const noexcept { return inputRays; }

    [[nodiscard]] vector<Node *> &getReceivers() { return receivers; }

    [[nodiscard]] vector<Node *> &getTiles() { return tiles; }

    [[nodiscard]] int getNumTiles() { return room.getNumTiles(); }

    [[nodiscard]] int getNumModes(int tileId) { return allNodes[tileId].getNumModes(); }

    [[nodiscard]] vector<double> &getDistribution(string &tileId, string &key) { return routingTables[tileId][key]; }


    friend void to_json(nlohmann::json &j, const Graph &g) {
        j = {
                {"allNodes", g.allNodes},
                {"allEdges", g.allEdges},
                {"inputRays", g.inputRays},
                {"routingTables", g.routingTables},
                {"txConfig", g.txConfig},
                {"tileConfig", g.tileConfig},
                {"room", g.room}
                // Note: receivers and tiles are omitted
        };
    }

    friend void from_json(const nlohmann::json &j, Graph &g) {
        j.at("allNodes").get_to(g.allNodes);
        j.at("allEdges").get_to(g.allEdges);
        j.at("inputRays").get_to(g.inputRays);
        j.at("routingTables").get_to(g.routingTables);
        j.at("txConfig").get_to(g.txConfig);
        j.at("tileConfig").get_to(g.tileConfig);
        j.at("room").get_to(g.room);
    }

    void loadGraph(string path, Graph &g) {
        try {
            std::ifstream file(path);  // Relative to working dir
            if (!file) {
                throw std::runtime_error("Could not open file!");
            }

            json j;
            file >> j;

            g = j.get<Graph>();  // Calls your from_json automatically

        } catch (const std::exception &e) {
            std::cerr << "Failed to load graph: " << e.what() << "\n";
        }

        for (Node &node: allNodes) {

            if (node.getType() == "Rx") receivers.push_back(&node);

            if (node.getType() == "Tile") tiles.push_back(&node);

        }

        // DEBUG: Write back to a new file
        std::ofstream out("test_output.json");
        if (out) {
            json j_out = g;  // Assumes to_json is defined
            out << j_out.dump(4);  // Pretty print with 4-space indent
            std::cout << "Graph written back to test_output.json\n";
        }


    }


};


#endif //PWEOPTIMIZATION_GRAPH_H
