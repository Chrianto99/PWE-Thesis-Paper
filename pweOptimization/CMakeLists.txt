cmake_minimum_required(VERSION 3.27)
project(pweOptimization)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(pweOptimization
        main.cpp

        include/Graph/Graph.h
        src/Graph/Graph.cpp

        include/Graph/Edge.h
        src/Graph/Edge.cpp

        include/Graph/Node.h
        src/Graph/Node.cpp

        include/Graph/Room.h
        src/Graph/Room.cpp

        include/Graph/TxConfig.h
        src/Graph/TxConfig.cpp

        include/Graph/TileConfig.h
        src/Graph/TileConfig.cpp

        include/Propagation/Ray.h
        src/Propagation/Ray.cpp

        include/Propagation/ModeHandler.h
        src/Propagation/ModeHandler.cpp

        include/Propagation/RayHandler.h
        src/Propagation/RayHandler.cpp

        include/Propagation/SystemState.h
        src/Propagation/SystemState.cpp

        include/Optimization/NSGA-II.h
        src/Optimization/NSGA-II.cpp

        include/Optimization/Solution.h

        include/Optimization/ParetoHandler.h
        src/Optimization/ParetoHandler.cpp
        include/Optimization/RBAS.h
        src/Optimization/RBAS.cpp
        include/Optimization/HyperVolumeCalculator.h
)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

# Disable tests
set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(json)

target_link_libraries(pweOptimization PRIVATE nlohmann_json::nlohmann_json)
