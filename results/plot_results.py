
import csv
import matplotlib.pyplot as plt
from pathlib import Path

folder = Path(__file__).parent

datasets = {
    "MPI Sum": "sum_results.csv",
    "Monte Carlo Pi": "pi_results.csv",
}

for name, filename in datasets.items():
    with open(folder / filename, newline="") as file:
        rows = list(csv.DictReader(file))

    processes = [int(row["processes"]) for row in rows]
    times = [float(row["time_seconds"]) for row in rows]
    speedups = [times[0] / t for t in times]

    plt.figure()
    plt.plot(processes, times, marker="o")
    plt.xlabel("Number of MPI Processes")
    plt.ylabel("Execution Time (seconds)")
    plt.title(f"{name}: Time vs Number of Processes")
    plt.xticks(processes)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(folder / f"{filename.replace('_results.csv', '_time.png')}")
    plt.close()

    plt.figure()
    plt.plot(processes, speedups, marker="o")
    plt.xlabel("Number of MPI Processes")
    plt.ylabel("Speedup")
    plt.title(f"{name}: Speedup vs Number of Processes")
    plt.xticks(processes)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(folder / f"{filename.replace('_results.csv', '_speedup.png')}")
    plt.close()

print("All four graphs saved in the results folder.")
