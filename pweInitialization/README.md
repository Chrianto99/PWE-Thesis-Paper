# Instructions:

## Prerequisites

* Java JDK installed
* Maven installed (`mvn -v` to check)

## Build and Run with Maven

1. **Navigate to the project directory**

```bash
cd /path/to/your/project
```

2. **Clean and build the project**

```bash
mvn clean install
```

* Downloads all dependencies 
* Compiles your code
* Runs tests (JUnit)
* Packages the app into a JAR in `target/`

3. **Run the project**
Run main.java


## Notes

* Every time a new dependency is added to `pom.xml`, run:

```bash
mvn clean install
```

to ensure all dependencies are downloaded and compiled.



# 📡 Programmable Wireless Environment (PWE) Graph Simulator

This project simulates a **Programmable Wireless Environment (PWE)** by generating a graph-based representation of the system. 

- **Nodes** represent system elements: **Transmitters (Tx)**, **Receivers (Rx)**, and **Software-Defined Metasurfaces (Tiles)**.
- **Edges** represent communication paths (with clear line-of-sight) between these elements.

The environment is a 3D room with randomly placed **spherical obstacles**, and the positions of all system components are randomized while maintaining **far-field distances** between them.

---

## 🚀 Quick Overview

To create a graph, call:

```java
createGraph(Room, TxConfig, TileConfig);
```

### 🧾 Input Parameters:

#### 1. `Room` object:
- `x`, `y`, `z` dimensions
- Number of **Users** (Receivers)
- Number of **Tiles**
- Path loss exponent `alpha`

#### 2. `TileConfig` object:
- Element spacing
- Element gain
- Number of elements
- Wavelength

#### 3. `TxConfig` object:
- Number of lobes
- Gain per lobe
- Transmit power
- Wavelength

---

## ⚙️ Handlers & Responsibilities

### 📌 RoomHandler
- Function: `createCuboidRoom(dimX,dimY,dimZ)`
- Handles room walls creation and obstacle placement

### 📌 NodeHandler
- Function: `initializeNodes()`
- Creates and places **Tx**, **Rx**, and **Tiles** in the room.

### 📌 EdgeHandler
- Function: `initializeEdges()`
- Connects nodes with **line-of-sight** edges (avoiding obstacle collisions).

### 📌 RadiationHandler
- Handles **ray emission** from the transmitter.
- Attempts to place the Tx such that all desired lobes can be emitted.
- If not possible (due to blockage), graph creation is **aborted and retried**.

### 📌 ModeHandler / DistributionManager
- Simulates **electromagnetic behavior** of Tiles (steering & diffusion).
- Manages the **routing table** for how signal power is redirected.

---

## 📘 Routing Table Structure

Each entry in the routing table describes how a Tile reflects incoming rays to various outputs.

### Format:
```
Given combination of : tileId || inputEdgeId || activeModeId --> (maps to) --> outputDistribution 
```

- `outputDistribution` is a list of `outputEdgeId.gain` values.
  - **Integer part** = `outputEdgeId`
  - **Decimal part** = gain as a percentage of max gain

### 🔑 Accessing Entries:

Use the following formula to get the index of a routing table entry:

```java
indexKey = tile.rTablePos + inputEdge.rTableKey * tile.numberOfModes + modeId;
```

- `rTablePos` → base index for the tile global index in routing Table . Defined during routing table creation 
- `rTableKey` → unique index for the input edge. Defined during routing table creation 
- `modeId` → selected electromagnetic id function id 

---

Final output Graph Object 
public class Graph {

    List<Edge> allEdges = new ArrayList<>();
    List<Node> allNodes = new ArrayList<>();
    List<Ray> inputRays = new ArrayList<>();
    List<double[]> routingTables = new ArrayList<>();
    TxConfig txConfig;
    TileConfig tileConfig;
    Room room;
}



## 🧪 Summary

This simulation models wireless propagation in a programmable 3D space with:

- Obstacle-aware path generation
- Realistic beamforming and transmission
- Smart reflection via software-defined metasurfaces
- Structured routing for power distribution



Feel free to explore and extend it for your own wireless research or simulation needs!



