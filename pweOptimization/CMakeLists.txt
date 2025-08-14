cmake_minimum_required(VERSION 3.27)
project(pweOptimization)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

include_directories(include)

add_executable(pweOptimization
        main.cpp

        include/Graph/Graph.h

        include/Graph/Edge.h

        include/Graph/Node.h

        include/Graph/Room.h

        include/Graph/TxConfig.h

        include/Graph/TileConfig.h

        include/Propagation/Ray.h

        include/Propagation/ModeHandler.h
        src/Propagation/ModeHandler.cpp

        include/Propagation/RayHandler.h
        src/Propagation/RayHandler.cpp

        include/Propagation/SystemState.h

        include/Optimization/NSGA-II.h
        src/Optimization/NSGA-II.cpp

        include/Optimization/Solution.h

        include/Optimization/ParetoHandler.h
        src/Optimization/ParetoHandler.cpp
        include/Optimization/RBAS.h
        src/Optimization/RBAS.cpp
        include/Optimization/HyperVolumeCalculator.h
        include/DataCollection/AlgorithmOutput.h
        include/DataCollection/DataHandler.h
        src/DataCollection/DataHandler.cpp

        include/Optimization/LocalSearch.h
        src/Optimization/LocalSearch.cpp
        include/Optimization/Algorithm.h
        include/Optimization/HERA.h
        src/Optimization/HERA.cpp
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
