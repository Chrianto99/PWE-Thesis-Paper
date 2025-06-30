//
// Created by Christos on 6/14/2025.
//

#include "Optimization/NSGA-II.h"
#include "Optimization/ParetoHandler.h"

void NSGAII::run() {

    vector<Solution> population = createInitialPopulation();//parallelize

    while (genCount < numGenerations) {

        if (genCount == 0) {
            ParetoHandler::fastNonDominatedSorting(population);
            ParetoHandler::calculateCrowdingDistance(population);
        }

        vector<Solution> offspringList = generateOffspring(population); //parallelize
        vector<Solution> offspring(offspringList.begin(), offspringList.end());
        population.insert(population.end(), offspring.begin(), offspring.end());


        ParetoHandler::fastNonDominatedSorting(population); //parallelize
        ParetoHandler::calculateCrowdingDistance(population); //parallelize
        paretoArchive = ParetoHandler::updateParetoArchive(paretoArchive, population, 200); //parallelize

//        if (ParetoHandler::checkRepetitionMarks(genCount * populationSize)){
//            output[genCount * populationSize] = paretoArchive;
//        }

        population = selectNextGeneration(population); //parallelize
        genCount++;
    }

}

vector<Solution> NSGAII::createInitialPopulation() {

    vector<Solution> population;
    int solutionGenerated = 0;

    while (solutionGenerated < populationSize) {

        SystemState systemState = rayHandler.propagateRandom();

        Solution newSol = Solution(systemState);

        totalSolsCreated++;
        solutionGenerated++;
        population.push_back(newSol);
    }

    return population;
}



vector<Solution> NSGAII::generateOffspring(vector<Solution>& population) {
    vector<Solution> offspring;
    int popSize = population.size();

    while (offspring.size() < popSize) {
        // Select parents using tournament selection
        Solution& parent1 = tournamentSelection(population);
        Solution& parent2 = tournamentSelection(population);

        uniform_real_distribution<double> realDist(0.0, 1.0);
        double randDouble = realDist(randGen);

        if (randDouble < crossoverChance) {
            Solution child = crossover(parent1, parent2);

            totalSolsCreated++;
            offspring.push_back(mutate(child));
        }
    }

    return offspring;
}



Solution NSGAII::crossover(const Solution& parent1,const Solution& parent2) {

    const vector<pair<int,int>> &modeList1 = parent1.getModeList();
    const vector<pair<int,int>> &modeList2 = parent2.getModeList();

    vector<pair<int,int>> offSpringModeList;


    for (int i = 0; i < modeList1.size(); ++i) {
        int mode = (rand() % 2 == 0) ? modeList1[i].second : modeList2[i].second;
        offSpringModeList.emplace_back(i,mode);
    }

    SystemState systemState = rayHandler.propagateGivenModes(offSpringModeList);
    Solution offspring = Solution(systemState);


    return offspring;
}

Solution NSGAII::mutate(Solution &solution) {

        for (auto& pair : solution.getModeList()) {

            uniform_real_distribution<double> realDist(0.0, 1.0);
            double randDouble = realDist(randGen);

            if (randDouble < mutationChance) {
                std::uniform_int_distribution<int> intDist(0, graph->getNumModes(0) - 1);
                pair.first = intDist(randGen);

            }

        }
    SystemState newSystemState = rayHandler.propagateGivenModes(solution.getModeList());
    Solution mutatedSolution = Solution(newSystemState);
    totalSolsCreated++;

    return mutatedSolution;

}

vector<Solution> NSGAII::selectNextGeneration(vector<Solution>& population) {

    auto compareFrontRank = [](Solution& a, Solution& b) {
        return a.getFrontRank() < b.getFrontRank() ;
    };
    std::sort(population.begin(), population.end(),compareFrontRank);
    vector<Solution> nextGeneration;

    for (auto& sol : population) {

        nextGeneration.push_back(sol);

        if (nextGeneration.size() == populationSize) return nextGeneration;

    }


    populationSize = (int)nextGeneration.size(); // optional if your size needs updating

    return nextGeneration;

}

Solution& NSGAII::tournamentSelection(const std::vector<Solution>& population) {
    std::uniform_int_distribution<int> dist(0, population.size() - 1);

    const Solution& a = population[dist(randGen)];
    const Solution& b = population[dist(randGen)];

    // Compare based on front rank, then crowding distance
    if (a.getFrontRank() < b.getFrontRank()) return const_cast<Solution&>(a);
    if (b.getFrontRank() < a.getFrontRank()) return const_cast<Solution&>(b);

    return (a.getCrowdingDistance() > b.getCrowdingDistance())
           ? const_cast<Solution&>(a)
           : const_cast<Solution&>(b);
}


//vector<Solution> NSGAII::generateOffspring(vector<Solution>& population) {
//    vector<Solution> offspring;
//    int numParents = population.size();
//
//    for (int i = 0; i < numParents - 1; ++i) {
//        for (int j = i + 1; j < numParents; ++j) {
//            Solution& parent1 = population[i];
//            Solution& parent2 = population[j];
//
//            double crossoverChance =
//                    (crossoverChance - 0.025 * parent1.getFrontRank()) +
//                    (crossoverChance - 0.025 * parent2.getFrontRank());
//
//            uniform_real_distribution<double> realDist(0.0, 1.0);
//            double randDouble = realDist(randGen);
//
//            if (randDouble < crossoverChance) {
//                Solution newOffspring = crossover(parent1, parent2);
//
//                if (newOffspring.getMinPower() < 0)  continue;
//
//                totalSolsCreated++;
//                offspring.push_back(newOffspring);
//            }
//        }
//    }
//
//    return offspring;
//}


