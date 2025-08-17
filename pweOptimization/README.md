# Telecommunication Propagation & Optimization Framework

## 📌 Overview
This project provides a **C++ simulation and optimization framework** for telecommunication systems consisting of:
- **Transmitters**
- **Software-Defined Metasurfaces (SDMs)**
- **Receivers**

The framework models the system as a **graph**, simulates **propagation** through the environment, and applies **multi-objective optimization algorithms** to improve receiver signal quality across multiple receivers.

### Key Features
- **Propagation Simulation**: Models electromagnetic signal propagation through SDMs.
- **Graph-Based Modeling**: The system topology is represented as a graph with nodes, edges, and tile configurations.
- **Multi-Objective Optimization**: Implements MOACO, NSGA-II, Local Search, and a custom algorithm (**HERA**).
- **Pareto Front Analysis**: Provides fast non-dominated sorting, crowding distance, and Pareto archive updates.
- **Monte Carlo Simulations**: Run large-scale tests and export results as JSON.

---

---

## 🔑 Handlers

- **`ParetoHandler`**
    - Maintains and updates the Pareto archive.
    - Implements **Fast Non-Dominated Sorting** and **Crowding Distance**.

- **`ModeHandler`**
    - Chooses electromagnetic functions for SDMs.
    - Uses **alias method sampling** to update mode distributions according to MOACO.

- **`RayHandler`**
    - Simulates propagation through the system.
    - Estimates received signal characteristics and system state.

- **`DataHandler`**
    - Runs full Monte Carlo simulations of multiple systems.
    - Executes optimization algorithms and captures **Pareto fronts**.
    - Exports results in **JSON** format.

---

## 🚀 Getting Started

### Prerequisites
- C++17 or newer
- CMake ≥ 3.10
- JSON library: [nlohmann/json](https://github.com/nlohmann/json)

### Build Instructions

```bash
mkdir build && cd build
cmake ..
make

