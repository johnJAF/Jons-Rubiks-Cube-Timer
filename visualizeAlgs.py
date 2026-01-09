import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

def list_session_files(algo_dir):
    files = [
        f for f in os.listdir(algo_dir)
        if f.endswith(".txt") and not f.lower().endswith("_keys.txt")
    ]
    if not files:
        print("No algorithm files found.")
        return []
    print("\nAvailable algorithm files:")
    for i, f in enumerate(files):
        print(f"{i+1}. {f}")
    return files

def load_session(filepath):
    cols = ["version", "id", "time_ms", "date"]

    rows = []
    with open(filepath, "r") as file:
        for line in file:
            parts = line.strip().split(":")
            if len(parts) == 4:
                rows.append(parts)

    df = pd.DataFrame(rows, columns=cols)

    df["id"] = pd.to_numeric(df["id"], errors="coerce")
    df["time_ms"] = pd.to_numeric(df["time_ms"], errors="coerce")
    df["time_s"] = df["time_ms"] / 1000.0
    df["date"] = pd.to_datetime(df["date"], format="%m/%d/%y", errors="coerce")

    df.dropna(subset=["id", "time_ms", "date"], inplace=True)

    df.sort_values(["date", "id"], inplace=True)
    df.reset_index(drop=True, inplace=True)

    return df

def plot_sessions(session_dfs):
    sns.set(style="whitegrid", context="talk")
    plt.figure(figsize=(10, 6))

    colors = sns.color_palette("husl", len(session_dfs))

    for (name, df), color in zip(session_dfs.items(), colors):
        x = np.arange(len(df))

        sns.regplot(
            x=x,
            y=df["time_s"].to_numpy(),
            scatter_kws={"alpha": 0.6},
            line_kws={"color": color},
            ci=None
        )

        plt.plot([], [], color=color, label=name)

    plt.title("Algo Times with Regression Line")
    plt.xlabel("Solve # (chronological)")
    plt.ylabel("Time (seconds)")
    plt.legend(title="File")
    plt.tight_layout()
    plt.show()

def main():
    print("=== Jon's Rubik's Cube Data Visualizer ===")

    firstChoice = input(
        "\nWould you like to visualize OLL (o) or PLL (p) "
        "(or -1 to go back): "
    ).strip().lower()

    if firstChoice == "o":
        algo_dir = os.path.join("Data", "Algorithms", "OLL")
    elif firstChoice == "p":
        algo_dir = os.path.join("Data", "Algorithms", "PLL")
    elif firstChoice == "-1":
        return
    else:
        print("Invalid choice.")
        return

    files = list_session_files(algo_dir)
    if not files:
        return

    choices = input(
        "\nEnter the number(s) of the file(s) to visualize "
        "(comma-separated, or -1 to go back): "
    ).strip()

    if choices == "-1":
        print("Returning without visualizing.")
        return

    indices = []
    for part in choices.split(","):
        part = part.strip()
        if part.isdigit():
            idx = int(part)
            if idx >= 1:
                indices.append(idx - 1)

    session_dfs = {}
    for i in indices:
        if 0 <= i < len(files):
            path = os.path.join(algo_dir, files[i])
            df = load_session(path)
            if not df.empty:
                session_dfs[files[i]] = df
                print(f"Loaded {files[i]} ({len(df)} solves)")

    if session_dfs:
        plot_sessions(session_dfs)
    else:
        print("No valid data to plot.")

if __name__ == "__main__":
    main()