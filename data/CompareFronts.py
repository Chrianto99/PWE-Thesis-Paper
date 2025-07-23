import json
import matplotlib.pyplot as plt
import sys

def plot_fronts(json_files):
    # Load all JSON files
    datasets = []
    for file in json_files:
        with open(file, 'r') as f:
            data = json.load(f)
            datasets.append(data)

    # Get all repetition keys (assuming all files have the same keys in "fronts")
    # Convert to dict for easier use
    repetition_keys = [front[0] for front in datasets[0]["fronts"]]

    # For each repetition (key), make a plot
    for rep_key in repetition_keys:
        plt.figure(figsize=(8, 6))

        for idx, dataset in enumerate(datasets):
            # Find the front for this repetition
            front_dict = dict(dataset["fronts"])
            if rep_key not in front_dict:
                continue  # Skip if not present in this dataset

            front_points = front_dict[rep_key]
            xs = [p[0] for p in front_points]
            ys = [p[1] for p in front_points]

            plt.plot(xs, ys, marker='o', label=f'File {idx+1}')

        plt.title(f"Front Comparison at repetition {rep_key}")
        plt.xlabel(datasets[0]["objectiveLabels"][0])
        plt.ylabel(datasets[0]["objectiveLabels"][1])
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.show()  # Or plt.savefig(f"fronts_{rep_key}.png")

if __name__ == "__main__":
    # Usage: python plot_fronts.py file1.json file2.json ...
    if len(sys.argv) < 2:
        print("Usage: python plot_fronts.py <file1.json> <file2.json> ...")
    else:
        plot_fronts(sys.argv[1:])
