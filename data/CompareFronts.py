import os
import json
import matplotlib.pyplot as plt

# === USER INPUT ===
# Path to the folder containing algorithm subfolders

numTiles = 16
numUsers = 4
project_root = f"{numTiles}Tiles_{numUsers}Users"

# Algorithm names (each is a su bfolder in project_root)
algorithm_names = ["RBAS", "NSGAII","BruteForce"]  # <-- Add yours here

# Repetition mark (0 = first, 1 = second, etc.)
repetition_mark = 0

# Number of plots per page (must be a perfect square like 9, 4, 16, etc.)
plots_per_page = 9


# === UTILITY FUNCTIONS ===
def load_fronts(json_path, reps):
    with open(json_path, 'r') as f:
        data = json.load(f)
        fronts = data.get("fronts", {})
        pair = fronts[3]
        return pair[1]


def collect_graph_names():
    """Assumes all algorithm folders contain same graph names."""
    example_algo = algorithm_names[0]
    algo_path = os.path.join(example_algo, project_root)
    print(algo_path)
    files = [f for f in os.listdir(algo_path) if f.endswith(".json")]
    return sorted([os.path.splitext(f)[0] for f in files])


def plot_grid(graph_names):

    total = len(graph_names)
    per_row = int(plots_per_page ** 0.5)
    fig, axs = plt.subplots(per_row, per_row, figsize=(12, 12))
    axs = axs.flatten()

    algorithm_styles = {
    "NSGAII": {"color": "red", "marker": "o"},
    "RBAS": {"color": "green", "marker": "s"},
    "BruteForce": {"color": "blue", "marker": "D"},
}

    for idx, graph_name in enumerate(graph_names):
        ax = axs[idx]
        for algo in algorithm_names:
            path = os.path.join( algo,project_root, f"{graph_name}.json")
            print(path)
            if not os.path.exists(path):
                continue
            points = load_fronts(path, repetition_mark)
            if not points:
                continue
            x, y = zip(*points)
            style = algorithm_styles.get(algo, {"color": "black", "marker": "x"})  # fallback
            ax.plot(x, y, 
            label=algo,
            marker=style["marker"],
            color=style["color"],
            markersize=3,
            linewidth=1,
            alpha=0.3)

            ax.set_title(graph_name)
            ax.set_xlabel("Objective 1")
            ax.set_ylabel("Objective 2")
            ax.legend(fontsize="small")

    # Turn off unused subplots
    for j in range(len(graph_names), plots_per_page):
        axs[j].axis("off")

    plt.tight_layout()
    plt.show()


# === MAIN EXECUTION ===
def main():
    all_graphs = collect_graph_names()
    for i in range(0, len(all_graphs), plots_per_page):
        batch = all_graphs[i:i + plots_per_page]
        plot_grid(batch)

if __name__ == "__main__":
    main()
