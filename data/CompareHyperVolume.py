import os
import json
import matplotlib.pyplot as plt
import numpy as np
from pymoo.indicators.hv import HV
from pymoo.util.nds.non_dominated_sorting import NonDominatedSorting

# === USER INPUT ===
numTiles = 16
numUsers = 4
roomDims = [10, 6, 4]
numGens = 49

results_path = f"Graphs_{roomDims[0]}x{roomDims[1]}x{roomDims[2]}/results/"
graph_path = f"/{numTiles}Tiles_{numUsers}Users"

algorithm_names = ["RBAS", "HERA","NSGAII","BruteForce"]

# Reference point for hypervolume (should be worse than all objective values)


# === UTILITY FUNCTIONS ===

def load_fronts_all_gens(json_path):
    with open(json_path, 'r') as f:
        data = json.load(f)
        fronts = data.get("fronts", {})
        return fronts  # dictionary: generation -> [front_id, points]

def compute_reference_point(all_graphs):
    worst = None
    for algo in algorithm_names:
        for graph_name in all_graphs:
            path = results_path + algo + graph_path + "/" + graph_name + ".json"
            if not os.path.exists(path):
                continue
            fronts = load_fronts_all_gens(path)
            for gen_data in fronts:
                if not gen_data:
                    continue
                points = gen_data[1]  # second element has the coordinates
                for p in points:
                    if worst is None:
                        worst = np.array(p)
                    else:
                        worst = np.maximum(worst, p)  # keep max per dimension
    return worst

reference_point = compute_reference_point

def load_fronts(json_path):
    with open(json_path, 'r') as f:
        data = json.load(f)
        fronts = data.get("fronts", {})
        return fronts

def collect_graph_names():
    example_algo = algorithm_names[0]
    algo_path = results_path + example_algo + graph_path
    files = [f for f in os.listdir(algo_path) if f.endswith(".json")]
    return sorted([os.path.splitext(f)[0] for f in files])

# === HYPERVOLUME COMPARISON ===
def plot_hypervolume_over_generations():
    all_graphs = collect_graph_names()
    generations = list(range(numGens))
    avg_hv_per_gen = {gen: {algo: [] for algo in algorithm_names} for gen in generations}
    hv = HV(ref_point=compute_reference_point(all_graphs))

    for graph_name in all_graphs:
        gen = int(graph_name.split('_')[1])
        for algo in algorithm_names:
            for gen in generations:

                path = results_path + algo + graph_path + "/" + graph_name + ".json"
                if not os.path.exists(path):
                    continue
                fronts = load_fronts(path)
                
                points = fronts[gen][1]

                avg_hv_per_gen[gen][algo].append(hv.do(np.array(points)))

    # Compute average hypervolume per generation
    avg_hv = {algo: [] for algo in algorithm_names}
    for gen in generations:
        for algo in algorithm_names:
            hv_values = avg_hv_per_gen[gen][algo]
            avg_hv[algo].append(np.mean(hv_values) if hv_values else 0.0)


    # Plotting
    plt.figure(figsize=(10, 6))
    for algo in algorithm_names:
        plt.plot(generations, avg_hv[algo], label=algo, marker='o')
    plt.xlabel('Generation')
    plt.ylabel('Average Hypervolume')
    plt.title(f'Average Hypervolume Over Generations (Generation )')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

# === MAIN EXECUTION ===
if __name__ == "__main__":
    plot_hypervolume_over_generations()