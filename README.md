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
  - Adds obstacles (spheres) that block specific signal paths.
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
    - **Minimum delay spread**

---

## 🏁 Simulation Pipeline

### Step 1: Run the Java Initializer
- **Purpose**: Creates the simulation environment and exports system graphs as JSON for the optimizer.
- **Steps**:
  1. Open and run `pwInitialization`.
  2. Inside `main()`, configure:
     - Room dimensions
     - Obstacles (spheres)
     - Number of SDMs (tiles)
     - Number of receivers
     - Transmitter configuration
     - Tile configuration
     - Number of graphs
- **Example (Java)**:
```java
double[] roomDims = new double[]{10, 6, 4};
int numSpheres = 5;
double pathLossExponent = 2;

RoomHandler roomHandler = new RoomHandler();
roomHandler.createCuboidRoom(roomDims);
roomHandler.addSpheres(numSpheres);

Room cuboidRoom = roomHandler.getRoom();
cuboidRoom.setAlpha(pathLossExponent);

TxConfig txConfig = new TxConfig(1600, 1, 0, wavelength);
TileConfig tileConfig = new TileConfig(40, wavelength / 10, 4, wavelength);

int[] numberOfTilesVector = {8, 16, 32};
int[] numReceiversVector = {2, 4};
int numberOfGraphs = 100;
```

### Step 2: Run the C++ Optimizer
- **Purpose**: Simulates EM propagation and performs multi-objective optimization.
- **Steps**:
  1. Open the C++ project.
  2. Run the optimizer using the `runSimulation()` function.
- **Example (C++)**:
```cpp
int roomDims[3] = {10, 6, 4};
DataHandler dataHandler = DataHandler();

dataHandler.setMOACOParams(2, 0.9, 0.7);
dataHandler.setNSGAParams(0.03);

dataHandler.runSimulation({
    "RBAS",     // Algorithm: "RBAS", "MOACO", "NSGA", "HERA"
    false,      // Local search flag
    16,         // Number of tiles
    4,          // Number of users
    100,        // Number of graphs
    50,         // Number of generations
    100,        // Number of repetitions
    roomDims    // Room dimensions
});
```

### Step 3: Analyze Results with Python
- **Purpose**: Post-process simulation outputs.
- **Scripts**:
  1. **Visualize Pareto fronts**:
  2. **Calculate Hypervolume
They exist in data folder of the project. Input desired graph data and algorithms to be compared and run them 
to visualize data



