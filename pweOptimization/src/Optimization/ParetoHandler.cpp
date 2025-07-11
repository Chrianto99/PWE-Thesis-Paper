//
// Created by Christos on 6/16/2025.
//
#include "Optimization/ParetoHandler.h"
void ParetoHandler::fastNonDominatedSorting(std::vector<Solution>& solutions) {
    std::vector<std::vector<Solution *>> fronts;
    std::map<Solution *, int> dominationCount;
    std::map<Solution *, std::vector<Solution *>> dominatedSolutions;

    // Step 1: Initialize domination info
    for (auto &p: solutions) {
        dominationCount[&p] = 0;
        dominatedSolutions[&p] = {};

        for (auto &q: solutions) {
            if (&p == &q) continue;

            if (dominates(p, q)) {
                dominatedSolutions[&p].push_back(&q);
            } else if (dominates(q, p)) {
                dominationCount[&p]++;
            }
        }

        // If p is not dominated by anyone, it's in front 0
        if (dominationCount[&p] == 0) {
            p.setFrontRank(0);
            if (fronts.empty()) {
                fronts.emplace_back();  // Create first front
            }
            fronts[0].push_back(&p);
        }
    }

    // Step 2: Build subsequent fronts
    int i = 0;
    while (i < fronts.size() && !fronts[i].empty()) {
        std::vector<Solution *> nextFront;

        for (auto *p: fronts[i]) {
            for (auto *q: dominatedSolutions[p]) {
                dominationCount[q]--;
                if (dominationCount[q] == 0) {
                    q->setFrontRank(i + 1);
                    nextFront.push_back(q);
                }
            }
        }

        if (!nextFront.empty()) {
            fronts.push_back(nextFront);
        }

        ++i;
    }
}


set<Solution> ParetoHandler::updateParetoArchive(set<Solution>& paretoArchive, vector<Solution>& newSolutions, int maxCapacity) {
    vector<Solution> combinedFront(paretoArchive.begin(), paretoArchive.end());
    combinedFront.insert(combinedFront.end(), newSolutions.begin(), newSolutions.end());

    set<Solution> updatedArchive;

    for (const auto& candidate : combinedFront) {
        bool isDominated = false;
        vector<Solution> toKeep;

        for (const auto& existing : updatedArchive) {
            if (dominates(existing, candidate)) {
                isDominated = true;
                break;
            }
            if (!dominates(candidate, existing)) {
                toKeep.push_back(existing);
            }
        }

        if (!isDominated) {
            updatedArchive.clear();
            for (const auto& sol : toKeep) {
                updatedArchive.insert(sol);
            }
            updatedArchive.insert(candidate);
        }
    }

    // Convert set to vector for crowding distance calculation and sorting
    vector<Solution> archiveVec(updatedArchive.begin(), updatedArchive.end());

    calculateCrowdingDistance(archiveVec);

    sort(archiveVec.begin(), archiveVec.end(), [](const Solution& a, const Solution& b) {
        return a.getCrowdingDistance() > b.getCrowdingDistance();
    });

    // Limit to max capacity
    if (archiveVec.size() > maxCapacity) {
        archiveVec.resize(maxCapacity);
    }

    return set<Solution>(archiveVec.begin(), archiveVec.end());
}

void ParetoHandler::calculateCrowdingDistance(vector<Solution>& solutions) {
    int n = solutions.size();
    if (n == 0) return;

    for (auto& sol : solutions) {
        sol.setCrowdingDistance(0.0);
    }

    if (n < 3) {
        // If fewer than 3 solutions, assign infinity to all
        for (auto& sol : solutions) {
            sol.setCrowdingDistance(numeric_limits<double>::infinity());
        }
        return;
    }

    // Get objective names from the first solution
    const auto objectivesCopy = solutions[0].getObjectives();


    for (const auto& pair : objectivesCopy) {


        const auto& objectiveName = pair.first;

        sort(solutions.begin(), solutions.end(),
                  [&objectiveName](const Solution& a, const Solution& b) {
                      return a.getObjectives().at(objectiveName) < b.getObjectives().at(objectiveName);
                  });

        // Assign infinite distance to boundary solutions
        solutions.front().setCrowdingDistance(numeric_limits<double>::infinity());
        solutions.back().setCrowdingDistance(numeric_limits<double>::infinity());

        double minObj = solutions.front().getObjectives().at(objectiveName);
        double maxObj = solutions.back().getObjectives().at(objectiveName);

        if (maxObj - minObj == 0.0)
            continue;  // Avoid division by zero

        // Compute normalized distances for the rest
        for (int i = 1; i < n - 1; ++i) {
            double prev = solutions[i - 1].getObjectives().at(objectiveName);
            double next = solutions[i + 1].getObjectives().at(objectiveName);
            double normDist = (next - prev) / (maxObj - minObj);

            double current = solutions[i].getCrowdingDistance();
            solutions[i].setCrowdingDistance(current + normDist);
        }
    }
}

bool ParetoHandler::dominates(const Solution& p, const Solution& q) {
    bool betterInAny = false;
    bool worseInAny = false;

    for (const auto& [key, p_val] : p.getObjectives()) {
        auto it = q.getObjectives().find(key);
        if (it == q.getObjectives().end()) {
            // Objective missing in q; cannot compare fairly
            continue;
        }

        double q_val = it->second;

        if (p_val < q_val) {
            betterInAny = true;
        } else if (p_val > q_val) {
            worseInAny = true;
        }

        if (worseInAny) break; // early exit: cannot dominate
    }

    return betterInAny && !worseInAny;
}

bool ParetoHandler::checkRepetitionMarks(int currentRepMark){

    vector<int> validMarks = {250, 500, 1000, 2000, 3000, 5000};

    if (find(validMarks.begin(), validMarks.end(), currentRepMark) != validMarks.end()) {
        return true;
    }

    return false;
}

map<int, set<Solution>> ParetoHandler::mergeOutputs(map<int, set<Solution>>& currentOutput, map<int, set<Solution>>& newOutput) {
    if (currentOutput.empty()) return newOutput;

    map<int, set<Solution>> updatedOutput;

    for (auto& kvP : currentOutput) {
        int repMark = kvP.first;
        set<Solution>& currentArchive = kvP.second;
        vector<Solution> newArchive(newOutput[repMark].begin(), newOutput[repMark].end());

        set<Solution> updatedArchive = updateParetoArchive(currentArchive, newArchive, 200);

        updatedOutput[repMark] = std::move(updatedArchive);
    }

    return updatedOutput;
}


