//
// Created by Christos on 3/18/2025.
//

#include "Graph/Graph.h"
void to_json(nlohmann::json& j, const Graph& g) {
    j = {
            {"allNodes", g.allNodes},
            {"allEdges", g.allEdges},
            {"inputRays", g.inputRays},
            {"txConfig", g.txConfig},
            {"tileConfig", g.tileConfig},
            {"room", g.room}
            // Note: receivers and tiles are omitted
    };
}

void from_json(const nlohmann::json& j, Graph& g) {
    j.at("allNodes").get_to(g.allNodes);
    j.at("allEdges").get_to(g.allEdges);
    j.at("inputRays").get_to(g.inputRays);
    j.at("txConfig").get_to(g.txConfig);
    j.at("tileConfig").get_to(g.tileConfig);
    j.at("room").get_to(g.room);
    // You will need to resolve and set `receivers` and `tiles` manually after loading
}

void Graph::loadGraph(string path, Graph& g){
    try {
        std::ifstream file(path);  // Relative to working dir
        if (!file) {
            throw std::runtime_error("Could not open file!");
        }

        json j;
        file >> j;

        g = j.get<Graph>();  // Calls your from_json automatically

    } catch (const std::exception& e) {
        std::cerr << "Failed to load graph: " << e.what() << "\n";
    }

    for (Node &node : allNodes) {

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

