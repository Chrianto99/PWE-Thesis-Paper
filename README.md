# SDM-Routing-Optimizer

This project simulates and optimizes **Software Defined Metasurfaces (SDMs)** in an enclosed indoor environment using hybrid programming: a **Java** system initializer and a **C++** optimizer.

---

## 🧠 Overview

This software models a **graph-based EM propagation system** using **Software Defined Metasurfaces (SDMs)**, **transmitters (Tx)**, **receivers (Rx)**, and **obstacles** within a defined 3D room. The purpose is to **optimize EM signal routing** for **power efficiency** and **minimum delay spread** using **bio-inspired algorithms**.

---

## 🔧 Components

### 1. **System Initializer (Java)**
- **Purpose**: Generates the simulation environment and network graph.
- **Functions**:
  - Randomly places SDMs, transmitters, and receivers on walls and ceiling.
  - Adds obstacles that block specific signal paths (using normal vectors).
  - Computes far-field EM propagation paths between all elements.
  - Simulates **SDM steering and diffusion functions**.
  - Builds and exports **routing tables** for all SDMs.
  - Outputs system data to be used by the C++ optimizer.

### 2. **System Optimizer (C++)**
- **Purpose**: Optimizes signal routing through SDMs for best EM performance.
- **Functions**:
  - Loads graph data and routing tables from Java initializer.
  - Models the EM network as a **directed graph**:
    - Nodes: SDMs, transmitters, receivers.
    - Edges: Valid EM propagation paths.
    - EM function: Maps input edges to output edges on SDMs.
  - Applies **Swarm Intelligence Algorithms**:
    - **Ant Colony Optimization**
    - **Genetic Algorithm**
  - Optimizes based on **Pareto conditions** for:
    - **Power efficiency**
    - **Delay spread**

---

## 📁 Project Structure

```plaintext
/SDM-Routing-Optimizer
├── /initializer-java/         # Java source code for system initializer
│   └── ...
├── /optimizer-cpp/            # C++ source code for optimizer
│   └── ...
├── /data/                     # Exported graph and routing tables
├── /docs/                     # Documentation and figures
└── README.md                  # You're here
