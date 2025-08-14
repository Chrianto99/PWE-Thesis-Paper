//
// Created by Christos on 6/14/2025.
//

#include "Optimization/NSGA-II.h"
#include "Optimization/ParetoHandler.h"

void NSGAII::run() {
    using namespace std::chrono;

    auto t_start = high_resolution_clock::now();
    auto t_end = high_resolution_clock::now();

    // Time initial population creation
    if (population.empty() || population.size() == 1) population = createInitialPopulation(); //parallelize

    int &genCount = algorithm->currentNumCycles;
    while (genCount < algorithm->numGenerations + 1) {

        if (genCount == 0) {

            ParetoHandler::fastNonDominatedSorting(population);

            ParetoHandler::calculateCrowdingDistance(population);
        }

        // Generate offspring
        vector<Solution> offspringList = generateOffspring(population); //parallelize
        vector<Solution> offspring(offspringList.begin(), offspringList.end());

        // Insert offspring into population
        population.insert(population.end(), offspring.begin(), offspring.end());

        if (algorithm->localSearch){
            algorithm->numLocalSearches = 1;
            LocalSearch::applyLocalSearch(*algorithm, population);
        }

        // Fast non-dominated sorting
        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(population); //parallelize

        // Crowding distance
        ParetoHandler::calculateCrowdingDistance(population); //parallelize

        // Update Pareto Archive
        ParetoHandler::updateParetoArchive(algorithm->paretoArchive, firstFront); //parallelize

        // Check repetition marks and store output
        if (ParetoHandler::checkRepetitionMarks(genCount * algorithm->genSize, algorithm->genSize)) {
            algorithm->output[genCount * algorithm->genSize] = algorithm->paretoArchive;
        }

        // Select next generation
        population = selectNextGeneration(population); //parallelize

        genCount++;
    }
}

vector<Solution> NSGAII::createInitialPopulation() {

    int solutionGenerated = 0;

    while (solutionGenerated < algorithm->genSize) {

        SystemState systemState = algorithm->rayHandler.propagate();
        if (systemState.getServiceRate() < 0.25) continue;
        Solution newSol = Solution(systemState);

        totalSolsCreated++;
        solutionGenerated++;
        population.push_back(newSol);
    }

    return population;
}

vector<Solution> NSGAII::inputInitialPopulation(set<Solution> &inputPopulation) {

    for (const Solution &sol: inputPopulation) {
        population.push_back(sol);
    }

    while (population.size() < algorithm->genSize) {

        set<Solution> firstFront = ParetoHandler::fastNonDominatedSorting(population);

        ParetoHandler::calculateCrowdingDistance(population);

        ParetoHandler::updateParetoArchive(algorithm->paretoArchive, firstFront);

        vector<Solution> offspring = generateOffspring(population);

        population.insert(population.end(), offspring.begin(), offspring.end());

    }

    if (population.size() > algorithm->genSize) selectNextGeneration(population);

    return population;
}


vector<Solution> NSGAII::generateOffspring() {
    vector<Solution> offspring;
    int popSize = population.size();

    while (offspring.size() < popSize) {
        // Select parents using tournament selection
        Solution &parent1 = tournamentSelection(population);
        Solution &parent2 = tournamentSelection(population);

        Solution child;
        while (child.getModeList().empty()) {
            child = crossover(parent1, parent2);
        }

        totalSolsCreated++;
        offspring.push_back(mutate(child));


    }

    return offspring;
}

vector<Solution> NSGAII::selectNextGeneration() {

    auto compareFrontRankCrowding = [](const Solution &a, const Solution &b) {
        if (a.getFrontRank() != b.getFrontRank()) {
            return a.getFrontRank() < b.getFrontRank();
        } else {
            // Crowding distance is sorted descending (larger better)
            return a.getCrowdingDistance() > b.getCrowdingDistance();
        }
    };

    std::sort(population.begin(), population.end(), compareFrontRankCrowding);
    vector<Solution> nextGeneration;

    for (auto &sol: population) {

        nextGeneration.push_back(sol);

        if (nextGeneration.size() == algorithm->genSize) return nextGeneration;

    }


    return nextGeneration;

}

Solution NSGAII::crossover(const Solution &parent1, const Solution &parent2) {
    const auto &modeList1 = parent1.getModeList();
    const auto &modeList2 = parent2.getModeList();

    unordered_map<int, int> map1, map2;

    // Convert parent1's mode list to map
    for (const auto &[nodeId, mode]: modeList1) {
        map1[nodeId] = mode;
    }

    // Convert parent2's mode list to map
    for (const auto &[nodeId, mode]: modeList2) {
        map2[nodeId] = mode;
    }

    unordered_set<int> allNodeIds;
    for (const auto &[id, _]: map1) allNodeIds.insert(id);
    for (const auto &[id, _]: map2) allNodeIds.insert(id);

    vector<pair<int, int>> offSpringModeList;

    for (int nodeId: allNodeIds) {
        bool in1 = map1.count(nodeId);
        bool in2 = map2.count(nodeId);

        int selectedMode = -1;

        if (in1 && in2) {
            // Both parents have this node: randomly select mode from one
            selectedMode = (rand() % 2 == 0) ? map1[nodeId] : map2[nodeId];
        } else if (in1 || in2) {
            // Only one parent has this node: maybe include it (e.g. 50% chance)
            if (rand() % 2 == 0) {
                selectedMode = in1 ? map1[nodeId] : map2[nodeId];
            }
        }

        if (selectedMode != -1) {
            offSpringModeList.emplace_back(nodeId, selectedMode);
        }
    }

    // Generate offspring SystemState using the chosen mode list
    SystemState systemState = algorithm->rayHandler.propagateGivenModes(offSpringModeList);
    if (systemState.getServiceRate() == 0) return Solution();
    return Solution(systemState);
}

Solution NSGAII::mutate(Solution &solution) {

    for (auto &pair: solution.getModeList()) {

        uniform_real_distribution<double> realDist(0.0, 1.0);
        double randDouble = realDist(algorithm->randGen);

        if (randDouble < mutationChance) {
            std::uniform_int_distribution<int> intDist(0, algorithm->graph->getNumModes(0) - 1);
            pair.first = intDist(algorithm->randGen);

        }

    }
    SystemState newSystemState = algorithm->rayHandler.propagateGivenModes(solution.getModeList());
    Solution mutatedSolution = Solution(newSystemState);
    totalSolsCreated++;

    return mutatedSolution;

}


Solution &NSGAII::tournamentSelection() {
    std::uniform_int_distribution<int> dist(0, population.size() - 1);

    const Solution &a = population[dist(algorithm->randGen)];
    const Solution &b = population[dist(algorithm->randGen)];

    // Compare based on front rank, then crowding distance
    if (a.getFrontRank() < b.getFrontRank()) return const_cast<Solution &>(a);
    if (b.getFrontRank() < a.getFrontRank()) return const_cast<Solution &>(b);

    return (a.getCrowdingDistance() > b.getCrowdingDistance())
           ? const_cast<Solution &>(a)
           : const_cast<Solution &>(b);
}



