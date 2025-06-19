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
    TxConfig txConfig;
    TileConfig tileConfig;
    Room room;

    vector<Node *> receivers;
    vector<Node *> tiles;

public:


    [[nodiscard]] vector<Node> &getAllNodes() noexcept { return allNodes; }

    Node &getNode(int id) noexcept { return allNodes[id]; }

    [[nodiscard]] const vector<Edge> &getAllEdges() const noexcept { return allEdges; }

    [[nodiscard]] Edge &getEdge(int id) noexcept { return allEdges[id]; }

    [[nodiscard]] const vector<Ray> &getInputRays() const noexcept { return inputRays; }


    [[nodiscard]] const TxConfig &getTxConfig() const noexcept { return txConfig; }

    [[nodiscard]] const TileConfig &getTileConfig() const noexcept { return tileConfig; }

    [[nodiscard]] const Room &getRoom() const noexcept { return room; }

    [[nodiscard]] vector<Node*> &getReceivers() {return receivers;}

    [[nodiscard]] vector<Node*> &getTiles() {return tiles;}

    [[nodiscard]] int getNumTiles(){return room.getNumTiles();}

    [[nodiscard]] int getNumModes(int tileId){return allNodes[tileId].getNumModes();}



    // Setters
    void setAllNodes(const std::vector<Node> &nodes) noexcept { allNodes = nodes; }

    void setAllEdges(const std::vector<Edge> &edges) noexcept { allEdges = edges; }

    void setInputRays(const std::vector<Ray> &rays) noexcept { inputRays = rays; }

    void setTxConfig(const TxConfig &config) noexcept { txConfig = config; }

    void setTileConfig(const TileConfig &config) noexcept { tileConfig = config; }

    void setRoom(const Room &r) noexcept { room = r; }

    void setReceivers() {
        for (Node &node: allNodes) {
            if (node.getType() == "Rx") {
                receivers.emplace_back(&node);
            }
        }
    }

    void setTiles() {
        for (Node &node: allNodes) {
            if (node.getType() == "Tile") {
                tiles.emplace_back(&node);
            }
        }
    }

    friend void to_json(nlohmann::json& j, const Graph& g);
    friend void from_json(const nlohmann::json& j, Graph& g);

    void loadGraph(string path, Graph& g);
    void printGraph();



};


#endif //PWEOPTIMIZATION_GRAPH_H
