import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# --- SETTINGS ---
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SESSIONS_DIR = os.path.join(BASE_DIR, "Data", "Sessions")

def list_session_files():
    files = [
    f for f in os.listdir(SESSIONS_DIR)
    if f.endswith(".txt") and not f.lower().endswith("_keys.txt")
    ]
    if not files:
        print("No session files found in Data/Sessions/")
        return []
    print("\nAvailable session files:")
    for i, f in enumerate(files):
        print(f"{i+1}. {f}")
    return files

def load_session(filepath):
    # we'll normalize into these columns (orientation can be None)
    cols = ["version", "id", "time_ms", "scramble", "orientation", "date"]

    rows = []
    with open(filepath, "r", encoding="utf-8") as file:
        for raw_line in file:
            line = raw_line.strip()
            if not line:
                continue

            # avoid exploding if later fields ever contain ':'
            # for v1 (6 fields) -> maxsplit 5
            # for v2 (5 fields) -> still fine, you'll just get 5 parts
            parts = line.split(":", 5)

            # skip headers if you ever have them
            if parts[0].lower().startswith("version"):
                continue

            if len(parts) == 6:
                # v1: version:id:time:scramble:orientation:date
                version, _id, time_ms, scramble, orientation, date = parts
            elif len(parts) == 5:
                # v2: version:id:time:scramble:date  (no orientation)
                version, _id, time_ms, scramble, date = parts
                orientation = None
            else:
                # malformed line
                continue

            rows.append([version, _id, time_ms, scramble, orientation, date])

    df = pd.DataFrame(rows, columns=cols)

    # types + conversions
    df["id"] = pd.to_numeric(df["id"], errors="coerce")
    df["time_ms"] = pd.to_numeric(df["time_ms"], errors="coerce")
    df["time_s"] = df["time_ms"] / 1000.0

    # keep your strict format if it's always mm/dd/yy, otherwise use flexible parsing:
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
        x = np.arange(len(df))  # <-- FIX: seaborn wants array-like, not range()

        sns.regplot(
            x=x,
            y=df["time_s"].to_numpy(),
            scatter_kws={"alpha": 0.6},
            line_kws={"color": color},
            ci=None
        )

        # regplot doesn't always respect label/legend cleanly across versions
        # so add an invisible line to create a reliable legend entry
        plt.plot([], [], color=color, label=name)

    plt.title("Session Solve Times with Regression Line")
    plt.xlabel("Solve # (chronological)")
    plt.ylabel("Time (seconds)")
    plt.legend(title="Session")
    plt.tight_layout()
    plt.show()

def main():
    print("=== Jon's Rubik's Cube Data Visualizer ===")

    files = list_session_files()
    if not files:
        return

    choices = input(
    "\nEnter the number(s) of the session(s) to visualize "
    "(comma-separated, or -1 to go back): "
    ).strip()

    # allow user to cancel
    if choices == "-1":
        print("Returning without visualizing sessions.")
        return

    indices = []
    for part in choices.split(","):
        part = part.strip()
        if part.lstrip("-").isdigit():
            idx = int(part)
            if idx >= 1:
                indices.append(idx - 1)

    session_dfs = {}
    for i in indices:
        if 0 <= i < len(files):
            path = os.path.join(SESSIONS_DIR, files[i])
            df = load_session(path)
            if not df.empty:
                session_dfs[files[i]] = df
                print(f"Loaded {files[i]} ({len(df)} solves)")

    if session_dfs:
        plot_sessions(session_dfs)
    else:
        print("No valid session data to plot.")

if __name__ == "__main__":
    main()